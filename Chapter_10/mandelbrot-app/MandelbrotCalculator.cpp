#include "MandelbrotCalculator.h"

#include <QDebug>
#include <QThread>

using namespace std;

const int JOB_RESULT_THRESHOLD = 10;

MandelbrotCalculator::MandelbrotCalculator(QObject* parent) :
    QTcpServer(parent),
     mMoveOffset(),
    mScaleFactor(),
    mAreaSize(),
    mIterationMax(),
    mReceivedJobResults(0),
    mWorkerClients(),
    mJobRequests(),
    mTimer()
{
    listen(QHostAddress::Any, 5000);
}

MandelbrotCalculator::~MandelbrotCalculator()
{
    while (!mWorkerClients.empty()) {
        removeWorkerClient(mWorkerClients.firstKey());
    }
}

void MandelbrotCalculator::generatePicture(QSize areaSize, QPointF moveOffset,
                                           double scaleFactor, int iterationMax)
{
    if (areaSize.isEmpty()) {
        return;
    }

    mTimer.start();
    clearJobs();

    mAreaSize = areaSize;
    mMoveOffset = moveOffset;
    mScaleFactor = scaleFactor;
    mIterationMax = iterationMax;

    for(int pixelPositionY = mAreaSize.height() - 1; pixelPositionY >= 0; pixelPositionY--) {
        mJobRequests.push_back(move(createJobRequest(pixelPositionY)));
    }

    for(WorkerClient* client : mWorkerClients.keys()) {
        sendJobRequests(*client, client->cpuCoreCount() * 2);
    }
}

void MandelbrotCalculator::process(WorkerClient* workerClient, JobResult jobResult)
{
    if (jobResult.areaSize != mAreaSize ||
                    jobResult.moveOffset != mMoveOffset ||
                    jobResult.scaleFactor != mScaleFactor) {
        return;
    }

    mReceivedJobResults++;
    mJobResults.append(jobResult);

    if (mJobResults.size() >= JOB_RESULT_THRESHOLD
                    || mReceivedJobResults == mAreaSize.height()) {
        emit pictureLinesGenerated(mJobResults);
        mJobResults.clear();
    }

    if (mReceivedJobResults < mAreaSize.height()) {
        sendJobRequests(*workerClient);
    } else {
        qDebug() << "Generated in" << mTimer.elapsed() << "ms";
    }
}

void MandelbrotCalculator::removeWorkerClient(WorkerClient* workerClient)
{
    qDebug() << "Removing workerClient";
    QThread* thread = mWorkerClients.take(workerClient);
    thread->quit();
    thread->wait(1000);
    delete thread;
    delete workerClient;
}

void MandelbrotCalculator::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "Connected workerClient";
    QThread* thread = new QThread(this);
    WorkerClient* client = new WorkerClient(socketDescriptor);
    int workerClientsCount = mWorkerClients.keys().size();
    mWorkerClients.insert(client, thread);
    client->moveToThread(thread);

    connect(this, &MandelbrotCalculator::abortAllJobs,
            client, &WorkerClient::abortJob);

    connect(client, &WorkerClient::unregistered,
            this, &MandelbrotCalculator::removeWorkerClient);
    connect(client, &WorkerClient::jobCompleted,
            this, &MandelbrotCalculator::process);

    connect(thread, &QThread::started,
            client, &WorkerClient::start);
    thread->start();

    if(workerClientsCount == 0 &&
        mWorkerClients.size() == 1) {
        generatePicture(mAreaSize, mMoveOffset, mScaleFactor, mIterationMax);
    }
}

std::unique_ptr<JobRequest> MandelbrotCalculator::createJobRequest(int pixelPositionY)
{
    auto jobRequest = make_unique<JobRequest>();
    jobRequest->pixelPositionY = pixelPositionY;
    jobRequest->moveOffset = mMoveOffset;
    jobRequest->scaleFactor = mScaleFactor;
    jobRequest->areaSize = mAreaSize;
    jobRequest->iterationMax = mIterationMax;
    return jobRequest;
}

void MandelbrotCalculator::sendJobRequests(WorkerClient& client, int jobRequestCount)
{
    QList<JobRequest> listJobRequest;
    for (int i = 0; i < jobRequestCount; ++i) {
        if (mJobRequests.empty()) {
            break;
        }

        auto jobRequest = move(mJobRequests.back());
        mJobRequests.pop_back();
        listJobRequest.append(*jobRequest);
    }

    if (!listJobRequest.empty()) {
        emit client.sendJobRequests(listJobRequest);
    }
}

void MandelbrotCalculator::clearJobs()
{
    mReceivedJobResults = 0;
    mJobRequests.clear();
    emit abortAllJobs();
}
