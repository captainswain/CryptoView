#ifndef CANDLESTICKDIALOG_H
#define CANDLESTICKDIALOG_H

#include <QString>
#include <QDialog>
#include <QtCharts>
#include <QCandlestickSeries>
#include <QChartView>
#include <QValueAxis>
#include <QDateTime>
#include <QApplication>
#include <QMainWindow>
#include <QtWebSockets/QWebSocket>
#include <QUrl>
#include <QList>
#include <QSslError>
#include <QAbstractSocket>
#include "coin_db.h"

namespace Ui {
class CandleStickDialog;
}

class CandleStickDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CandleStickDialog(QString symbol, QWidget *parent = 0);
    void open(const QUrl &url);
    ~CandleStickDialog();

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onSslErrors(const QList<QSslError> &errors);
    void onError(QAbstractSocket::SocketError error);

private:
    void makeChart();

private:
    Ui::CandleStickDialog *ui;
    QCandlestickSeries *m_coinSeries;
    QChart *m_chart;
    QChartView *m_chartView;
    QStringList m_categories;
//    QBarCategoryAxis *axisX;
//    QValueAxis *axisY;

    QString m_symbol;
    QWebSocket *m_webSocket;
    DbManager *db;

};

#endif // CANDLESTICKDIALOG_H
