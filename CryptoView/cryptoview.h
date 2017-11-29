#ifndef CRYPTOVIEW_H
#define CRYPTOVIEW_H

#include "coin.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLabel>

namespace Ui {
class CryptoView;
}

class CryptoView : public QMainWindow
{
    Q_OBJECT

public:
    void setCurrencyLabelText(QString currencyName, float value, float trend, QLabel& titleLabel, QLabel& valueLabel );
    explicit CryptoView(QWidget *parent = 0);
    void updatelabel(QString str);
    void LoadValues();
    ~CryptoView();

private slots:
    void on_addCurrencyBtn_clicked();
    void requestFinished(QNetworkReply *);
    void btcRequest();

    void on_goBackBtn_clicked();

private:
    Ui::CryptoView *ui;
    QNetworkAccessManager *qnam;
};

#endif // CRYPTOVIEW_H
