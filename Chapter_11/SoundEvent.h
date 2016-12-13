#ifndef SOUNDEVENT_H
#define SOUNDEVENT_H

#include <QtGlobal>
#include "Serializable.h"

class SoundEvent : public Serializable
{
public:
    SoundEvent(qint64 timestamp = 0, int soundId = 0);
    ~SoundEvent();

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    qint64 timestamp;
    int soundId;
};

#endif // SOUNDEVENT_H
