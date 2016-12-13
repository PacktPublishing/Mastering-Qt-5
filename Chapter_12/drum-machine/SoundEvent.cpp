#include "SoundEvent.h"


SoundEvent::SoundEvent(qint64 timestamp, int soundId) :
    Serializable(),
    timestamp(timestamp),
    soundId(soundId)
{
}

SoundEvent::~SoundEvent()
{
}

QVariant SoundEvent::toVariant() const
{
    QVariantMap map;
    map.insert("timestamp", timestamp);
    map.insert("soundId", soundId);
    return map;
}

void SoundEvent::fromVariant(const QVariant& variant)
{
    QVariantMap map = variant.toMap();
    timestamp = map.value("timestamp").toLongLong();
    soundId = map.value("soundId").toInt();
}
