#include "DatabaseManager.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QStandardPaths>

void DatabaseManager::debugQuery(const QSqlQuery& query)
{
    if (query.lastError().type() == QSqlError::ErrorType::NoError) {
        qDebug() << "Query OK:"  << query.lastQuery();
    } else {
       qWarning() << "Query KO:" << query.lastError().text();
       qWarning() << "Query text:" << query.lastQuery();
    }
}

DatabaseManager& DatabaseManager::instance()
{
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
    QFile assetDbFile(":/database/" + DATABASE_FILENAME);
    QString destinationDbFile = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)
                    .append("/" + DATABASE_FILENAME);

    qDebug() << "Assets file" << assetDbFile.fileName();
    qDebug() << "Database file" << destinationDbFile;
    if (assetDbFile.exists()) {
        qDebug() << "File exist in assets!!!!";
        if (!QFile::exists(destinationDbFile)) {

            assetDbFile.copy(destinationDbFile);
            QFile::setPermissions(destinationDbFile, QFile::WriteOwner | QFile::ReadOwner);
            qDebug() << "Setted permissions on copied file";
        }
    }
    static DatabaseManager singleton(destinationDbFile);
#else
    static DatabaseManager singleton;
#endif
    return singleton;
}

DatabaseManager::DatabaseManager(const QString& path) :
    mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    albumDao(*mDatabase),
    pictureDao(*mDatabase)
{
    mDatabase->setDatabaseName(path);

    bool openStatus = mDatabase->open();
    qDebug() << "Database connection: " << (openStatus ? "OK" : "Error");

    albumDao.init();
    pictureDao.init();
}

DatabaseManager::~DatabaseManager()
{
    mDatabase->close();
}

