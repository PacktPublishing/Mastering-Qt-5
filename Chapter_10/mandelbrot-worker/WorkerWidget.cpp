#include "WorkerWidget.h"

#include <QVBoxLayout>

WorkerWidget::WorkerWidget(QWidget *parent) :
    QWidget(parent),
    mStatus(this),
    mWorker(),
    mWorkerThread(this),
    mRefreshTimer()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(&mStatus);

    mWorker.moveToThread(&mWorkerThread);

    connect(&mRefreshTimer, &QTimer::timeout, [this] {
        mStatus.setMaximum(mWorker.receivedJobsCounter());
        mStatus.setValue(mWorker.sentJobCounter());
    });

    mWorkerThread.start();
    mRefreshTimer.start(100);
}

WorkerWidget::~WorkerWidget()
{
    mWorkerThread.quit();
    mWorkerThread.wait(1000);
}
