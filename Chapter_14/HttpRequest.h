#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class HttpRequest : public QObject
{
    Q_OBJECT
public:
    HttpRequest(QObject* parent = 0);

    void executeAll();
    void executeGet();
    void executePost();
    void executeBlockingGet();

private slots:
    void replyFinished(QNetworkReply* reply);
    void replyReadyRead();

private:
    QNetworkAccessManager mAccessManager;
};

#endif // HTTPREQUEST_H
