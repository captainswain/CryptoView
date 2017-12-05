#include "httpclient.h"

#include <QNetworkRequest>

HTTPClient::HTTPClient(QObject *parent) : QObject(parent)
{
    qnam = new QNetworkAccessManager(this);
    connect(qnam, &QNetworkAccessManager::finished, this, &HTTPClient::onFinished);
    connect(qnam, &QNetworkAccessManager::sslErrors, this, &HTTPClient::onSslErrors);
}

// Get request to provided url
QNetworkReply * HTTPClient::get(QUrl url)
{
    QNetworkRequest request(url);

    // Send and return the request
    return qnam->get(request);
}

// On data received
void HTTPClient::onFinished(QNetworkReply *reply)
{
    // Emit to our response slot
    emit response(reply);
}

// On any type of ssl errors
void HTTPClient::onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug() << errors.first();
}
