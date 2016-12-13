#include "MainWindow.h"

#include <QApplication>
#include <QList>

#include "JobRequest.h"
#include "JobResult.h"
#include "WorkerClient.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<QList<JobRequest>>();
    qRegisterMetaType<QList<JobResult>>();
    qRegisterMetaType<WorkerClient*>();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
