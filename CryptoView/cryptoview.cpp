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

    // Grab rank and set to variable
    int rank = coin.getRank();

    // Use switch to check what rank, and call helper function with correct labels.
    switch (rank) {
    case 1:
        setCurrencyLabelText(coin, *ui->coin1_img, *ui->coin1_value, *ui->coin1_title);
        break;
    case 2:
        setCurrencyLabelText(coin, *ui->coin2_img, *ui->coin2_value, *ui->coin2_title);
        break;
    case 3:
        setCurrencyLabelText(coin, *ui->coin3_img, *ui->coin3_value, *ui->coin3_title);
        break;
    case 4:
        setCurrencyLabelText(coin, *ui->coin4_img, *ui->coin4_value, *ui->coin4_title);
        break;
    default:
        break;
    }



    qDebug() << "Rank is: " << rank;


}

//Helper class to update ui
void CryptoView::setCurrencyLabelText(coin& coin, QLabel& imgLabel, QLabel& valueLabel, QLabel& titleLabel ){

    //check coin trend then set colors accordingly.
    if(coin.getPercent_change_1h() > 0){
        valueLabel.setText("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'.SF NS Text'; font-size:13pt; font-weight:400; font-style:normal;\"><p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#ffffff;\">" + QString::number(coin.getPrice_usd()) + "</span><span style=\" font-size:14pt; color:#45bf55;\"> " +QString::number(coin.getPercent_change_1h()) +" % </span></p></body></html>");
    }else{
        valueLabel.setText("<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; color:#ffffff;\">"+ QString::number(coin.getPrice_usd()) +"<span style=\"color: #EA5455\"> " +QString::number(coin.getPercent_change_1h()) +"%    </span></span></p></body></html>");
    }

    //Set Coin title
    titleLabel.setText("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'Helvetica Neue'; font-size:14pt; font-weight:400; font-style:normal;\"><p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica Neue,Helvetica,Arial,sans-serif'; font-size:24px; font-weight:496; color:#ffffff;\">" + coin.getSymbol() + "</span></p></body></html>");


    QString abreviation = coin.getSymbol();

    QPixmap mypix (":resources/white-logos/" + abreviation.toLower() + ".png");
    imgLabel.setPixmap(mypix);

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
       qDebug() << json_obj["percent_change_1h"].toString();

       //create coin object
       coin tempCoin;

       tempCoin.setRank(json_obj["rank"].toString().toInt());
       tempCoin.setName(json_obj["name"].toString());
       tempCoin.setSymbol(json_obj["symbol"].toString());
       tempCoin.setPrice_usd(json_obj["price_usd"].toString().toFloat());
       //percent_change_1h
       tempCoin.setPercent_change_1h(json_obj["percent_change_1h"].toString().toFloat());
       pushCoin(tempCoin);
   }
}

void CryptoView::on_goBackBtn_clicked()
{
   // Go back to crypto dashboard homepage
   ui->stackedWidget->setCurrentWidget(ui->homePageWidget);
}
