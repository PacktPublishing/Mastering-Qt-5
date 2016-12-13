#include "PlaybackWorker.h"

#include <QElapsedTimer>
#include <QThread>

#include "Track.h"
#include "SoundEvent.h"

PlaybackWorker::PlaybackWorker(const Track& track, QObject *parent) :
    QObject(parent),
    mTrack(track),
    mIsPlaying(false)
{
}

void PlaybackWorker::play()
{
    mIsPlaying.store(true);
    QElapsedTimer timer;
    size_t soundEventIndex = 0;
    const auto& soundEvents = mTrack.soundEvents();

    timer.start();
    while(timer.elapsed() <= mTrack.duration()
          && mIsPlaying.load()) {
        if (soundEventIndex < soundEvents.size()) {
            const auto& soundEvent = soundEvents.at(soundEventIndex);

            if (timer.elapsed() >= soundEvent->timestamp) {
                emit playSound(soundEvent->soundId);
                soundEventIndex++;
            }
        }
        QThread::msleep(1);
    }

    if (soundEventIndex >= soundEvents.size()) {
        emit trackFinished();
    }
}

void PlaybackWorker::stop()
{
   mIsPlaying.store(false);
}
