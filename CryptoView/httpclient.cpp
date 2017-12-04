#include "httpclient.h"

#include <QNetworkRequest>

HTTPClient::HTTPClient(QObject *parent) : QObject(parent)
{
    qnam = new QNetworkAccessManager(this);
    connect(qnam, &QNetworkAccessManager::finished, this, &HTTPClient::onFinished);
    connect(qnam, &QNetworkAccessManager::sslErrors, this, &HTTPClient::onSslErrors);
}

QNetworkReply * HTTPClient::get(QUrl url)
{
    QNetworkRequest request(url);

    return qnam->get(request);
}

void HTTPClient::onFinished(QNetworkReply *reply)
{
    emit response(reply);
}

void HTTPClient::onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug() << errors.first();
}
