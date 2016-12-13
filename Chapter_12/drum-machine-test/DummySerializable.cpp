#include "DummySerializable.h"

DummySerializable::DummySerializable() :
    Serializable()
{
}

QVariant DummySerializable::toVariant() const
{
    QVariantMap map;
    map.insert("myInt", myInt);
    map.insert("myDouble", myDouble);
    map.insert("myString", myString);
    map.insert("myBool", myBool);
    return map;
}

void DummySerializable::fromVariant(const QVariant& variant)
{
    QVariantMap map = variant.toMap();
    myInt = map.value("myInt").toInt();
    myDouble = map.value("myDouble").toDouble();
    myString = map.value("myString").toString();
    myBool = map.value("myBool").toBool();
}
