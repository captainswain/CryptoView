#include "cryptoview.h"
#include "ui_cryptoview.h"
#include "coin.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

CryptoView::CryptoView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CryptoView)
{
    ui->setupUi(this);
    qnam = new QNetworkAccessManager(this);

    //Lock Size
    this->setFixedSize(this->width(),this->height());

    this->LoadValues();
}

CryptoView::~CryptoView()
{
    delete ui;
}

void CryptoView::on_addCurrencyBtn_clicked()
{
    //coin btc = new coin();
   btcRequest();
}


void CryptoView::setCurrencyLabelText(QString currencyName, float value, float trend, QLabel& titleLabel, QLabel& valueLabel ){

    // Eventually pass currency object to update a label group
}

void CryptoView::LoadValues()
{
    // This is ran when the form is constructed
    // Imagine form.load in VS
}

void CryptoView::btcRequest()
{
    // Example usage of a get HTTP request
    QUrl url("https://api.coinmarketcap.com/v1/ticker/?limit=4");
    QNetworkRequest request(url);

    // Connect our finished sinal to the requestFinished slot
    connect(qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply *)));

    // Send the get request
    qnam->get(request);
}

void CryptoView::requestFinished(QNetworkReply *reply)
{
    // Read all data from the reply
    QString strReply = (QString)reply->readAll();

    // Parse JSON
    // Might be a better way of doing this
    QJsonDocument jsonDoc = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonArray json_array = jsonDoc.array();

   foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();

       // Output JSON items in JSON object
       qDebug() << json_obj["name"].toString();
       qDebug() << json_obj["symbol"].toString();
       qDebug() << json_obj["price_usd"].toString();
       qDebug() << json_obj["last_updated"].toString();
   }
}

void CryptoView::on_goBackBtn_clicked()
{
   // Go back to crypto dashboard homepage
   ui->stackedWidget->setCurrentWidget(ui->homePageWidget);
}
