#ifndef TESTGUI_H
#define TESTGUI_H

#include <QTest>

#include "MainWindow.h"

class TestGui : public QObject
{
    Q_OBJECT
public:
    TestGui(QObject* parent = nullptr);

private slots:
    void controlButtonState();
    void playSound();

private:
    MainWindow mMainWindow;
};

#endif // TESTGUI_H
