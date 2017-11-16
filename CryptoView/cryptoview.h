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
<<<<<<< HEAD
    void updatelabel(QString str);
=======
>>>>>>> c901fc3999a1725f893a80fd5d59f9d12e3bbced
    void LoadValues();
    ~CryptoView();

private slots:
    void on_addCurrencyBtn_clicked();
    void requestFinished(QNetworkReply *);

private:
    Ui::CryptoView *ui;
    QNetworkAccessManager *qnam;
};

#endif // CRYPTOVIEW_H
