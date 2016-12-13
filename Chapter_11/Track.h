#ifndef TRACK_H
#define TRACK_H

#include <memory>
#include <vector>
#include <QObject>
#include <QVector>
#include <QElapsedTimer>

#include "Serializable.h"
#include "SoundEvent.h"

class Track : public QObject, public Serializable
{
    Q_OBJECT
public:
    enum class State {
        STOPPED,
        PLAYING,
        RECORDING,
    };

    explicit Track(QObject *parent = 0);
    ~Track();

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    State state() const;
    State previousState() const;
    quint64 elapsedTime() const;
    const std::vector<std::unique_ptr<SoundEvent>>& soundEvents() const;

    qint64 duration() const;

signals:
    void stateChanged(State state);

public slots:
    void play();
    void record();
    void stop();
    void addSoundEvent(int soundEventId);

private:
    void clear();
    void setState(State state);

private:
    qint64 mDuration;
    std::vector<std::unique_ptr<SoundEvent>> mSoundEvents;
    QElapsedTimer mTimer;
    State mState;
    State mPreviousState;
};

#endif // TRACK_H
