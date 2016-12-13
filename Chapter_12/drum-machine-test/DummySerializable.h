#ifndef DUMMYSERIALIZABLE_H
#define DUMMYSERIALIZABLE_H

#include "Serializable.h"

class DummySerializable : public Serializable
{
public:
    DummySerializable();

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    int myInt = 0;
    double myDouble = 0.0;
    QString myString = "";
    bool myBool = false;
};

#endif // DUMMYSERIALIZABLE_H
