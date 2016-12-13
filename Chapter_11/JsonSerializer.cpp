#include "JsonSerializer.h"

#include <QJsonDocument>
#include <QFile>

JsonSerializer::JsonSerializer() :
    Serializer()
{
}

void JsonSerializer::save(const Serializable& serializable, const QString& filepath, const QString& /*rootName*/)
{
    QJsonDocument doc = QJsonDocument::fromVariant(serializable.toVariant());
    QFile file(filepath);
    file.open(QFile::WriteOnly);
    file.write(doc.toJson());
    file.close();
}

void JsonSerializer::load(Serializable& serializable, const QString& filepath)
{
    QFile file(filepath);
    file.open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    serializable.fromVariant(doc.toVariant());
}
