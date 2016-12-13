#ifndef PLAYBACKWORKER_H
#define PLAYBACKWORKER_H

#include <QObject>
#include <QAtomicInteger>

class Track;

class PlaybackWorker : public QObject
{
    Q_OBJECT
public:
    explicit PlaybackWorker(const Track& track, QObject *parent = 0);

signals:
    void playSound(int soundId);
    void trackFinished();

public slots:
    void play();
    void stop();

private:
    const Track& mTrack;
    QAtomicInteger<bool> mIsPlaying;
};

#endif // PLAYBACKWORKER_H
