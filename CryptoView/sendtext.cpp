/* #include "sendtext.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QByteArray>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QNetworkAccessManager>

sendText::sendText(QObject *parent) : QObject(parent)
{
    // Create JSON body
    QVariantMap feed;
    feed.insert("7149045913",QVariant(mobile_number).toString());
    feed.insert("test message",QVariant(message).toString());
    QByteArray payload=QJsonDocument::fromVariant(feed).toJson();

    qDebug() << Qvariant(payload).toString();

    // Set API URL
    QUrl myurl;
    myurl.setScheme("https"); //https also applicable
    myurl.setHost("api.trumpia.com");
    myurl.setPath("/rest/v1/vuskeedoo/sms");

    qDebug() << myurl.toString();

    // Submit request and create header
    QNetworkRequest request;
    request.setUrl(myurl);
    request.setRawHeader("X-Apikey", "7f5a72d074cff3222bfa0b079af236fc")
    request.setHeader(QNetworkRequest::ContentTypeHeader,
    "application/json");

    QNetworkAccessManager *restclient; //in class
    restclient = new QNetworkAccessManager(this); //constructor
    QNetworkReply *reply = restclient->post(request,payload);
    qDebug() << reply->readAll();

    // Traverse array and add into database
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj = jsdoc.object();
    QJsonArray jsarr = jsobj["feeds"].toArray();
    foreach (const QJsonValue &value, jsarr) {
    QJsonObject jsob = value.toObject();
    qDebug() << jsob["request_id"].toString();
    qDebug() << jsob["sms_id"].toInt();
    }
    reply->deleteLater();
}
*/
