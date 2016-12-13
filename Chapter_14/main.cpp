#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QCommandLineParser>

#include "HttpRequest.h"
#include "Person.h"

void messageHander(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
    QString levelText;
    switch (type) {
        case QtDebugMsg:
            levelText = "Debug";
            break;
        case QtInfoMsg:
            levelText = "Info";
            break;
        case QtWarningMsg:
            levelText = "Warning";
            break;
        case QtCriticalMsg:
            levelText = "Critical";
            break;
        case QtFatalMsg:
            levelText = "Fatal";
            break;
    }
    QString text = QString("[%1] %2")
                        .arg(levelText)
                        .arg(message);
    QFile file("app.log");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream textStream(&file);
    textStream << text << endl;
}

void generateRandom()
{
    // case 1
    qDebug() << "-- case 1 --";
    qDebug() << "first number is" << qrand() % 10;
    qDebug() << "second number is" << qrand() % 10;

    // case 2
    qDebug() << "-- case 2 --";
    qsrand(3);
    qDebug() << "first number is" << qrand() % 10;
    qDebug() << "second number is" << qrand() % 10;

    // case 3
    qDebug() << "-- case 3 --";
    qsrand(QDateTime::currentDateTime().toTime_t());
    qDebug() << "first number is" << qrand() % 10;
    qDebug() << "second number is" << qrand() % 10;

}

void commandLineInterface(QCoreApplication& app)
{
    QCoreApplication::setApplicationName("ch14-hat-tips");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("CLI helper");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOptions({
        {"debug",
         "Enable the debug mode."},

        {{"f", "file"},
         "Write the logs into <file>.",
         "logfile"},

        {{"l", "level"},
        "Restrict the logs to level <level>. Default is 'fatal'.",
        "level",
        "fatal"},
    });

    parser.process(app);

    qDebug() << "debug mode:" << parser.isSet("debug");
    qDebug() << "file:" << parser.value("file");
    qDebug() << "level:" << parser.value("level");
}

void memoryViewer()
{
    bool boolean = true;
    int integer = 5;
    char character = 'A';
    int* integerPointer = &integer;

    qDebug() << "boolean is:" << boolean;
    qDebug() << "integer is:" << integer;
    qDebug() << "character is:" << character;
    qDebug() << "integerPointer is:" << integerPointer;
    qDebug() << "*integerPointer is:" << *integerPointer;
    qDebug() << "done!";
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Saving your logs to a file
    // (uncomment it to save console messages to the 'app.log' file)
    //qInstallMessageHandler(messageHander);

    // Generating random numbers
    generateRandom();

    // Logging custom objects to QDebug
    Person person = { "Lenna", 64 };
    qDebug() << "Person info" << person;

    // Improving log messages
    qSetMessagePattern("[%{time yyyy-MM-dd hh:mm:ss}] [%{type}] %{function} %{message}");
    qInfo() << "Application starting...";

    // Generating a command-line interface
    commandLineInterface(app);

    // Sending and Receiving HTTP data
    HttpRequest http;
    http.executeAll();

    // Examining the memory with Qt Creator
    memoryViewer();

    return app.exec();
}
