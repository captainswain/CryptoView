#ifndef CRYPTOVIEW_H
#define CRYPTOVIEW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class CryptoView;
}

class CryptoView : public QMainWindow
{
    Q_OBJECT

public:
    explicit CryptoView(QWidget *parent = 0);
    void updatelabel(QString str);
    void LoadValues();
    ~CryptoView();

private slots:
    void on_addCurrencyBtn_clicked();
    void requestFinished(QNetworkReply *);

    void on_goBackBtn_clicked();

private:
    Ui::CryptoView *ui;
    QNetworkAccessManager *qnam;
};

#endif // CRYPTOVIEW_H
