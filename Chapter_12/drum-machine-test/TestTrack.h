#ifndef TESTTRACK_H
#define TESTTRACK_H

#include <QTest>

class TestTrack : public QObject
{
    Q_OBJECT
public:
    explicit TestTrack(QObject *parent = 0);

private slots:
    void addSoundEvent_data();
    void addSoundEvent();
};

#endif // TESTTRACK_H
