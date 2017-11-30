#include "cryptoview.h"
#include "ui_cryptoview.h"
#include "coin.h"
#include "timer.h"

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
   // On click, grab JSON
   btcRequest();
}

void CryptoView::LoadValues()
{
    // This is ran when the form is constructed
    // Imagine form.load in VS
}

// Function to GET JSON data from URL
void CryptoView::btcRequest()
{
    // GET request to pull JSON data
    QUrl url("https://api.coinmarketcap.com/v1/ticker/?limit=4");
    QNetworkRequest request(url);

    // Connect our finished signal to the requestFinished slot
    connect(qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply *)));

    // Send the GET request
    qnam->get(request);
}

// Function to parse JSON data
void CryptoView::requestFinished(QNetworkReply *reply)
{
    // Read all data from the reply
    QString strReply = (QString)reply->readAll();

    // Parse JSON
    // Might be a better way of doing this
    QJsonDocument jsonDoc = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonArray json_array = jsonDoc.array();

    // Sava coin data into array
    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();

       // Output JSON items in JSON object
       qDebug() << json_obj["id"].toString();
       qDebug() << json_obj["name"].toString();
       qDebug() << json_obj["symbol"].toString();
       qDebug() << json_obj["rank"].toString();
       qDebug() << json_obj["id"].toString();
       qDebug() << json_obj["price_usd"].toString();
       qDebug() << json_obj["price_btc"].toString();
       qDebug() << json_obj["last_updated"].toString();
   }
}
