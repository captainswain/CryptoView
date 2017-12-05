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

// On socket open
void SocketClient::open(const QUrl &url, QList<QString> symbols)
{
    m_symbols = symbols;
    m_webSocket.open(QUrl(url));
}

// On socket connected
void SocketClient::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &SocketClient::onTextMessageReceived);

    // send subscribe to channel message
    for (int i = 0; i < m_symbols.size(); ++i)
        m_webSocket.sendTextMessage("{\"channel\":\"ticker\",\"event\":\"subscribe\",\"symbol\":\"t" + m_symbols.at(i).toUpper() + "USD\"}");
}

// WebSocket on data receieved
void SocketClient::onTextMessageReceived(QString message)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    if (jsonDoc.isEmpty() || jsonDoc.isNull())
        return;

    if (jsonDoc.isObject())
    {
        // JSON data is an object
        QJsonObject obj = jsonDoc.object();
        if (obj.value("event").toString() == "subscribed")
        {
            // If we subscribe to a channel emit channel data
            emit newCoin(obj.value("chanId").toInt(), obj.value("pair").toString());
        }
    }
    else if (jsonDoc.isArray())
    {
        // JSON data is an array
        QJsonArray arr = jsonDoc.array();

        // Drop heartbeat message
        if (arr.at(1).toString() == "hb")
            return;

        // Emit coin data on ticker update
        QJsonArray selected = arr.at(1).toArray();

        // Build a coin
        CoinData tempCoin;
        tempCoin.bid = selected.at(0).toInt();
        tempCoin.bidSize = selected.at(1).toDouble();
        tempCoin.ask = selected.at(2).toInt();
        tempCoin.askSize = selected.at(3).toDouble();
        tempCoin.dailyChange = selected.at(4).toDouble();
        tempCoin.dailyChangePercent = selected.at(5).toDouble();
        tempCoin.lastPrice = selected.at(6).toDouble();
        tempCoin.volume = selected.at(7).toDouble();
        tempCoin.high = selected.at(8).toInt();
        tempCoin.low = selected.at(9).toInt();

        emit coinUpdate(arr.at(0).toInt(), tempCoin);
    }
}

// On any type of ssl errors
void SocketClient::onSslErrors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors);

    // WARNING: Never ignore SSL errors in production code.
    // The proper way to handle self-signed certificates is to add a custom root
    // to the CA store.
    // TODO: Handle SSL errors

    m_webSocket.ignoreSslErrors();
}

// On any type of error that may happen with the socket
void SocketClient::onError(QAbstractSocket::SocketError error)
{
    qDebug() << m_webSocket.errorString();
}
