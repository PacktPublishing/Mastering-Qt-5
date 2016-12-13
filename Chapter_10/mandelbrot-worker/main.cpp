#include <QApplication>

#include "JobResult.h"

#include "WorkerWidget.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<JobResult>();

    QApplication a(argc, argv);
    WorkerWidget workerWidget;

    workerWidget.show();
    return a.exec();
}
