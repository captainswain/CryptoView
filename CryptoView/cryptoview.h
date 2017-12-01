#ifndef CRYPTOVIEW_H
#define CRYPTOVIEW_H

#include "coin.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLabel>
#include <QTimer>

namespace Ui {
class CryptoView;
}

class CryptoView : public QMainWindow
{
    Q_OBJECT

public:
    void setCurrencyLabelText(coin& coin, QLabel& imgLabel, QLabel& valueLabel, QLabel& titleLabel );
    void pushCoin(coin& coin);
    explicit CryptoView(QWidget *parent = 0);
    void updatelabel(QString str);
    void formLoad();
    ~CryptoView();

private slots:
    void on_addCurrencyBtn_clicked();
    void requestFinished(QNetworkReply *);
    void btcRequest();

    void on_goBackBtn_clicked();

private:
    Ui::CryptoView *ui;
    QNetworkAccessManager *qnam;
    QTimer *timer;
};

#endif // CRYPTOVIEW_H
