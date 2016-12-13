#include "BinarySerializer.h"

#include <QFile>
#include <QDataStream>

BinarySerializer::BinarySerializer() :
    Serializer()
{
}

void BinarySerializer::save(const Serializable& serializable, const QString& filepath, const QString& /*rootName*/)
{
    QFile file(filepath);
    file.open(QFile::WriteOnly);
    QDataStream dataStream(&file);
    dataStream << serializable.toVariant();
    file.close();
}

void BinarySerializer::load(Serializable& serializable, const QString& filepath)
{
    QFile file(filepath);
    file.open(QFile::ReadOnly);
    QDataStream dataStream(&file);
    QVariant variant;
    dataStream >> variant;
    serializable.fromVariant(variant);
    file.close();
}
