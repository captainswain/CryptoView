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

    // Start timer to get data
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(btcRequest()));
    timer->start(15000); // 15000ms TODO: Make this be changable

    // Load Currency Values from api and do all form load
    formLoad();
}

CryptoView::~CryptoView()
{
    delete ui;
}

void CryptoView::on_addCurrencyBtn_clicked()
{
    //Show next page
    ui->stackedWidget->setCurrentWidget(ui->addCurrencyWidget);
}


void CryptoView::pushCoin(coin& coin){

    int rank = coin.getRank();

    qDebug() << "Rank is: " << rank;


}

//Helper class to update ui
void CryptoView::setCurrencyLabelText(QString currencyName, float value, float trend, QLabel& titleLabel, QLabel& valueLabel ){

    // Eventually pass currency object to update a label group
}


//Form Load
void CryptoView::formLoad()
{
    btcRequest();
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
       qDebug() << json_obj["rank"].toString();
       qDebug() << json_obj["name"].toString();
       qDebug() << json_obj["symbol"].toString();
       qDebug() << json_obj["price_usd"].toString();
       qDebug() << json_obj["last_updated"].toString();

       //create coin object
       coin tempCoin;

       tempCoin.setRank(json_obj["rank"].toString().toInt());
       tempCoin.setName(json_obj["name"].toString());
       tempCoin.setSymbol(json_obj["symbol"].toString());
       tempCoin.setPrice_usd(json_obj["price_usd"].toString().toFloat());

       pushCoin(tempCoin);
   }
}

void CryptoView::on_goBackBtn_clicked()
{
   // Go back to crypto dashboard homepage
   ui->stackedWidget->setCurrentWidget(ui->homePageWidget);
}
