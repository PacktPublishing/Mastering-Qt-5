#include "TestJsonSerializer.h"
#include "TestTrack.h"
#include "TestGui.h"

#include <QMap>
#include <QDebug>

#include <memory>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList arguments = QCoreApplication::arguments();

    map<QString, unique_ptr<QObject>> tests;
    tests.emplace("gui", make_unique<TestGui>());
    tests.emplace("jsonserializer", make_unique<TestJsonSerializer>());
    tests.emplace("track", make_unique<TestTrack>());

    if (arguments.size() >= 3 && arguments[1] == "-select") {
        QString testName = arguments[2];
        auto iter = tests.begin();
        while(iter != tests.end()) {
            if (iter->first != testName) {
                iter = tests.erase(iter);
            } else {
                ++iter;
            }
        }
        arguments.removeOne("-select");
        arguments.removeOne(testName);
    }

    int status = 0;
    for(auto& test : tests) {
        status |= QTest::qExec(test.second.get(), arguments);
    }

    return status;
}
