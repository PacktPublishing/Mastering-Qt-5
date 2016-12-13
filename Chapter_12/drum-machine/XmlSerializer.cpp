#include "XmlSerializer.h"

#include <QFile>

XmlSerializer::XmlSerializer() :
    Serializer()
{
}

void XmlSerializer::save(const Serializable& serializable, const QString& filepath, const QString& rootName)
{
    QFile file(filepath);
    file.open(QFile::WriteOnly);
    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    writeVariantToStream(rootName, serializable.toVariant(), stream);
    stream.writeEndDocument();
    file.close();
}

void XmlSerializer::load(Serializable& serializable, const QString& filepath)
{
    QFile file(filepath);
    file.open(QFile::ReadOnly);
    QXmlStreamReader stream(&file);
    stream.readNextStartElement();
    serializable.fromVariant(readVariantFromStream(stream));
}

void XmlSerializer::writeVariantToStream(const QString& nodeName, const QVariant& variant, QXmlStreamWriter& stream)
{
    stream.writeStartElement(nodeName);
    stream.writeAttribute("type", variant.typeName());

    switch (variant.type()) {
        case QMetaType::QVariantList:
            writeVariantListToStream(variant, stream);
            break;
        case QMetaType::QVariantMap:
            writeVariantMapToStream(variant, stream);
            break;
        default:
            writeVariantValueToStream(variant, stream);
            break;
    }

    stream.writeEndElement();
}

void XmlSerializer::writeVariantValueToStream(const QVariant& variant, QXmlStreamWriter& stream)
{
    stream.writeCharacters(variant.toString());
}

void XmlSerializer::writeVariantListToStream(const QVariant& variant, QXmlStreamWriter& stream)
{
    QVariantList list = variant.toList();

    for(const QVariant& element : list) {
        writeVariantToStream("item", element, stream);
    }
}

void XmlSerializer::writeVariantMapToStream(const QVariant& variant, QXmlStreamWriter& stream)
{
    QVariantMap map = variant.toMap();
    QMapIterator<QString, QVariant> i(map);

    while (i.hasNext()) {
        i.next();
        writeVariantToStream(i.key(), i.value(), stream);
    }
}

QVariant XmlSerializer::readVariantFromStream(QXmlStreamReader& stream)
{
    QXmlStreamAttributes attributes = stream.attributes();
    QString typeString = attributes.value("type").toString();

    QVariant variant;
    switch (QVariant::nameToType(typeString.toStdString().c_str())) {
        case QMetaType::QVariantList:
            variant = readVariantListFromStream(stream);
            break;
        case QMetaType::QVariantMap:
            variant = readVariantMapFromStream(stream);
            break;
        default:
            variant = readVariantValueFromStream(stream);
            break;
    }

    return variant;
}

QVariant XmlSerializer::readVariantValueFromStream(QXmlStreamReader& stream)
{
    QXmlStreamAttributes attributes = stream.attributes();
    QString typeString = attributes.value("type").toString();
    QString dataString = stream.readElementText();

    QVariant variant(dataString);
    variant.convert(QVariant::nameToType(typeString.toStdString().c_str()));
    return variant;
}

QVariant XmlSerializer::readVariantListFromStream(QXmlStreamReader& stream)
{
    QVariantList list;
    while(stream.readNextStartElement()) {
        list.append(readVariantFromStream(stream));
    }
    return list;
}

QVariant XmlSerializer::readVariantMapFromStream(QXmlStreamReader& stream)
{
    QVariantMap map;
    while(stream.readNextStartElement()) {
        map.insert(stream.name().toString(), readVariantFromStream(stream));
    }
    return map;
}
