#include "Track.h"

using namespace std;

Track::Track(QObject *parent) :
    QObject(parent),
    Serializable(),
    mDuration(0),
    mSoundEvents(),
    mTimer(),
    mState(State::STOPPED),
    mPreviousState(mState)
{
}

Track::~Track()
{
}

QVariant Track::toVariant() const
{
    QVariantMap map;
    map.insert("duration", mDuration);

    QVariantList list;
    for (const auto& soundEvent : mSoundEvents) {
        list.append(soundEvent->toVariant());
    }
    map.insert("soundEvents", list);

    return map;
}

void Track::fromVariant(const QVariant& variant)
{
    QVariantMap map = variant.toMap();
    mDuration = map.value("duration").toLongLong();

    QVariantList list = map.value("soundEvents").toList();
    for(const QVariant& data : list) {
        auto soundEvent = make_unique<SoundEvent>();
        soundEvent->fromVariant(data);
        mSoundEvents.push_back(move(soundEvent));
    }
}

void Track::play()
{
    setState(State::PLAYING);
    mTimer.start();
}

void Track::record()
{
    clear();
    setState(State::RECORDING);
    mTimer.start();
}

void Track::stop()
{
    if (mState == State::RECORDING) {
        mDuration = mTimer.elapsed();
    }
    setState(State::STOPPED);
}

void Track::addSoundEvent(int soundEventId)
{
    if (mState != State::RECORDING) {
        return;
    }
    mSoundEvents.push_back(make_unique<SoundEvent>(
                               mTimer.elapsed(),
                               soundEventId));
}

void Track::clear()
{
    mSoundEvents.clear();
    mDuration = 0;
}

void Track::setState(Track::State state)
{
    mPreviousState = mState;
    mState = state;
    emit stateChanged(mState);
}

qint64 Track::duration() const
{
    return mDuration;
}

const std::vector<std::unique_ptr<SoundEvent> >& Track::soundEvents() const
{
    return mSoundEvents;
}

Track::State Track::state() const
{
    return mState;
}

Track::State Track::previousState() const
{
    return mPreviousState;
}

quint64 Track::elapsedTime() const
{
    return mTimer.elapsed();
}

