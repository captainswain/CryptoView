#include "socketclient.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

SocketClient::SocketClient(QObject *parent) : QObject(parent)
{
    qDebug() << "WebSocket created";
    connect(&m_webSocket, &QWebSocket::connected, this, &SocketClient::onConnected);
    connect(&m_webSocket, &QWebSocket::sslErrors, this, &SocketClient::onSslErrors);
    connect(&m_webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &SocketClient::onError);
    //connect(&m_webSocket, &QWebSocket::disconnected, this, &WebClient::onDisconnected);
}

void SocketClient::open(const QUrl &url, QList<QString> symbols)
{
    m_symbols = symbols;

    m_webSocket.open(QUrl(url));
}

void SocketClient::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &SocketClient::onTextMessageReceived);

    // send subscribe to channel message
    for (int i = 0; i < m_symbols.size(); ++i)
        m_webSocket.sendTextMessage("{\"channel\":\"ticker\",\"event\":\"subscribe\",\"symbol\":\"t" + m_symbols.at(i).toUpper() + "USD\"}");
}

void SocketClient::onTextMessageReceived(QString message)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    if (jsonDoc.isEmpty() || jsonDoc.isNull())
        return;

    if (jsonDoc.isObject())
    {
        QJsonObject obj = jsonDoc.object();
        if (obj.value("event").toString() == "subscribed")
        {
            // If we subscribe to a channel emit channel data
            emit newCoin(obj.value("chanId").toInt(), obj.value("pair").toString());
        }
    }
    else if (jsonDoc.isArray())
    {
        QJsonArray arr = jsonDoc.array();

        // Drop heartbeat message
        if (arr.at(1).toString() == "hb")
            return;

        // Emit coin data on ticker update
        emit coinUpdate(arr.at(0).toInt(), arr.at(1).toArray().at(6).toDouble());
    }
}

void SocketClient::onSslErrors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors);

    // WARNING: Never ignore SSL errors in production code.
    // The proper way to handle self-signed certificates is to add a custom root
    // to the CA store.
    // TODO: Handle SSL errors

    m_webSocket.ignoreSslErrors();
}

void SocketClient::onError(QAbstractSocket::SocketError error)
{
    qDebug() << m_webSocket.errorString();
}
