#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

#include "Message.h"
#include "JobResult.h"

class Job;
class JobRequest;

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(QObject* parent = 0);
    ~Worker();

    int receivedJobsCounter() const;
    int sentJobCounter() const;

signals:
    void abortAllJobs();

private slots:
    void readMessages();

private:
    void sendRegister();
    void sendJobResult(JobResult jobResult);
    void sendUnregister();
    void handleJobRequest(Message& message);
    void handleAllJobsAbort(Message& message);
    Job* createJob(const JobRequest& jobRequest);

private:
    QTcpSocket mSocket;
    QDataStream mSocketReader;
    int mReceivedJobsCounter;
    int mSentJobsCounter;
};

#endif // WORKER_H
