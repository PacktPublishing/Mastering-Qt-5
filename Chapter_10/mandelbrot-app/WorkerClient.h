#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QTcpSocket>
#include <QList>
#include <QDataStream>

#include "JobRequest.h"
#include "JobResult.h"
#include "Message.h"

class WorkerClient : public QObject
{
    Q_OBJECT
public:
    WorkerClient(int socketDescriptor);

    int cpuCoreCount() const;

signals:
    void unregistered(WorkerClient* workerClient);
    void jobCompleted(WorkerClient* workerClient, JobResult jobResult);
    void sendJobRequests(QList<JobRequest> requests);

public slots:
    void start();
    void abortJob();

private slots:
    void doSendJobRequests(QList<JobRequest> requests);
    void readMessages();

private:
    void handleWorkerRegistered(Message& message);
    void handleWorkerUnregistered(Message& message);
    void handleJobResult(Message& message);

private:
    int mSocketDescriptor;
    int mCpuCoreCount;
    QTcpSocket mSocket;
    QDataStream mSocketReader;
};

Q_DECLARE_METATYPE(WorkerClient*)

#endif // WORKERTHREAD_H
