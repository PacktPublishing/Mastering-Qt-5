#include "TestTrack.h"

#include "Track.h"

TestTrack::TestTrack(QObject *parent) : QObject(parent)
{
}

void TestTrack::addSoundEvent_data()
{
    QTest::addColumn<int>("trackState");
    QTest::addColumn<int>("soundEventCount");

    QTest::newRow("STOPPED") << static_cast<int>(Track::State::STOPPED) << 0;
    QTest::newRow("PLAYING") << static_cast<int>(Track::State::PLAYING) << 0;
    QTest::newRow("RECORDING") << static_cast<int>(Track::State::RECORDING) << 1;
}

void TestTrack::addSoundEvent()
{
    QFETCH(int, trackState);
    QFETCH(int, soundEventCount);

    Track track;
    switch (static_cast<Track::State>(trackState)) {
        case Track::State::STOPPED:
            track.stop();
            break;
        case Track::State::PLAYING:
            track.play();
            break;
        case Track::State::RECORDING:
            track.record();
            break;
        default:
            break;
    }

    track.addSoundEvent(0);
    track.stop();

    QCOMPARE(track.soundEvents().size(), static_cast<size_t>(soundEventCount));
}
