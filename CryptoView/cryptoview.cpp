#include "cryptoview.h"
#include "ui_cryptoview.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

CryptoView::CryptoView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CryptoView)
{
    ui->setupUi(this);
    qnam = new QNetworkAccessManager(this);
    this->LoadValues();
}

CryptoView::~CryptoView()
{
    delete ui;
}

void CryptoView::on_addCurrencyBtn_clicked()
{
    ui->label_11->setText("Hello");

    // Example usage of a get HTTP request
    // QUrl url("https://api.coinmarketcap.com/v1/ticker/?limit=5");
    QUrl url("https://api.coinmarketcap.com/v1/ticker/bitcoin/");
    QNetworkRequest request(url);

    // Connect our finished sinal to the requestFinished slot
    connect(qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply *)));

    // Send the get request
    qnam->get(request);
}

void CryptoView::LoadValues()
{
    // This is ran when the form is constructed
    // Imagine form.load in VS
}

void CryptoView::requestFinished(QNetworkReply *reply)
{
    // Read all data from the reply
    QString strReply = (QString)reply->readAll();

    // Parse JSON
    // Might be a better way of doing this
    QJsonDocument jsonDoc = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonDoc.array();
    QJsonObject obj = jsonArr.first().toObject();

    // Output JSON items in JSON object
    qDebug() << obj["name"].toString();
    qDebug() << obj["symbol"].toString();
    qDebug() << obj["price_usd"].toString();
    qDebug() << obj["last_updated"].toString();

}
