#include "TestGui.h"

#include <QPushButton>
#include <QtTest/QtTest>

#include "SoundEffectWidget.h"

TestGui::TestGui(QObject* parent) :
    QObject(parent),
    mMainWindow()
{
    QTestEventLoop::instance().enterLoop(1);
}

void TestGui::controlButtonState()
{
    QPushButton* stopButton = mMainWindow.findChild<QPushButton*>("stopButton");
    QPushButton* playButton = mMainWindow.findChild<QPushButton*>("playButton");
    QPushButton* recordButton = mMainWindow.findChild<QPushButton*>("recordButton");

    QTest::mouseClick(recordButton, Qt::LeftButton);

    QCOMPARE(stopButton->isEnabled(), true);
    QCOMPARE(playButton->isEnabled(), false);
    QCOMPARE(recordButton->isEnabled(), false);
}

void TestGui::playSound()
{
    SoundEffectWidget widget;
    QSignalSpy spy(&widget, &SoundEffectWidget::soundPlayed);
    widget.setId(2);
    widget.play();

    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).toInt(), 2);
}

