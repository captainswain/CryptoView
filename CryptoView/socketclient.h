#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QUrl>
#include <QString>
#include <QList>
#include <QSslError>
#include <QAbstractSocket>
#include <QJsonObject>

struct CoinData
{
    int bid;
    double bidSize;
    int ask;
    double askSize;
    double dailyChange;
    double dailyChangePercent;
    double lastPrice;
    double volume;
    int high;
    int low;
};

class SocketClient : public QObject
{
    Q_OBJECT
public:
    explicit SocketClient(QObject *parent = nullptr);
    void open(const QUrl &url, QList<QString> symbols);

signals:
    void coinUpdate(int channelId, CoinData data);
    void newCoin(int channelId, QString pair);

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onSslErrors(const QList<QSslError> &errors);
    void onError(QAbstractSocket::SocketError error);

private:
    QWebSocket m_webSocket;
    QList<QString> m_symbols;
};

#endif // SOCKETCLIENT_H
