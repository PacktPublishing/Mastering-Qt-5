#ifndef TESTJSONSERIALIZER_H
#define TESTJSONSERIALIZER_H

#include <QtTest/QTest>

#include "JsonSerializer.h"

class TestJsonSerializer : public QObject
{
    Q_OBJECT

public:
    TestJsonSerializer(QObject* parent = nullptr);

private slots:
    void cleanup();
    void saveDummy();
    void loadDummy();

    void saveTrack_data();
    void saveTrack();

private:
    QString loadFileContent();

private:
    JsonSerializer mSerializer;
};

#endif // TESTJSONSERIALIZER_H
