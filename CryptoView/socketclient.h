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

class SocketClient : public QObject
{
    Q_OBJECT
public:
    explicit SocketClient(QObject *parent = nullptr);
    void open(const QUrl &url, QList<QString> symbols);

signals:
    void coinUpdate(int channelId, double price);
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
