#include "TestJsonSerializer.h"

#include "DummySerializable.h"
#include "Track.h"

const QString FILENAME = "test.json";
const QString DUMMY_FILE_CONTENT = "{\n    \"myBool\": true,\n    \"myDouble\": 5.2,\n    \"myInt\": 1,\n    \"myString\": \"hello\"\n}\n";

TestJsonSerializer::TestJsonSerializer(QObject* parent) :
    QObject(parent),
    mSerializer()
{
}

void TestJsonSerializer::cleanup()
{
    QFile(FILENAME).remove();
}

void TestJsonSerializer::saveDummy()
{
    DummySerializable dummy;
    dummy.myInt = 1;
    dummy.myDouble = 5.2;
    dummy.myString = "hello";
    dummy.myBool = true;

    mSerializer.save(dummy, FILENAME);

    QString data = loadFileContent();
    QVERIFY(data == DUMMY_FILE_CONTENT);
}

void TestJsonSerializer::loadDummy()
{
    QFile file(FILENAME);
    file.open(QFile::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << DUMMY_FILE_CONTENT;
    file.close();

    DummySerializable dummy;
    mSerializer.load(dummy, FILENAME);

    QCOMPARE(dummy.myInt, 1);
    QCOMPARE(dummy.myDouble, 5.2);
    QCOMPARE(dummy.myString, QString("hello"));
    QCOMPARE(dummy.myBool, true);
}

void TestJsonSerializer::saveTrack_data()
{
    QTest::addColumn<int>("soundEventCount");

    QTest::newRow("1") << 1;
    QTest::newRow("100") << 100;
    QTest::newRow("1000") << 1000;
}

void TestJsonSerializer::saveTrack()
{
    QFETCH(int, soundEventCount);
    Track track;
    track.record();
    for (int i = 0; i < soundEventCount; ++i) {
        track.addSoundEvent(i % 4);
    }
    track.stop();

    QBENCHMARK {
        mSerializer.save(track, FILENAME);
    }
}

QString TestJsonSerializer::loadFileContent()
{
    QFile file(FILENAME);
    file.open(QFile::ReadOnly);
    QString content = file.readAll();
    file.close();
    return content;
}
