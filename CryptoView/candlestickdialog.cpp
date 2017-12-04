#include "candlestickdialog.h"
#include "ui_candlestickdialog.h"
#include <QtCharts>

CandleStickDialog::CandleStickDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CandleStickDialog)
{

    ui->setupUi(this);

    QStringList categories;
    QCandlestickSeries *coinSeries = new QCandlestickSeries();

    //    //Creating set (example)
    //    QCandlestickSet *coinSet = new QCandlestickSet(timestamp);
    //    coinSet->setOpen(open);
    //    coinSet->setClose(close);
    //    coinSet->setHigh(high);
    //    coinSet->setLow(low);
    //

    //    //Push to series
    //    coinSeries->append(coinSet);

    //    //Push timestamp to categories
    //    categories << QDateTime::fromMSecsSinceEpoch(set->timestamp()).toString("dd");


    //Creating set (example)
    QCandlestickSet *coinSet = new QCandlestickSet(1512345600000);
    coinSet->setOpen(11161);
    coinSet->setClose(11458);
    coinSet->setHigh(11600);
    coinSet->setLow(10718);

    QCandlestickSet *coinSettwo = new QCandlestickSet(1512259200000);
    coinSettwo->setOpen(10881);
    coinSettwo->setHigh(11162);
    coinSettwo->setLow(11874);
    coinSettwo->setClose(10161);

    QCandlestickSet *coinSetthree = new QCandlestickSet(1512172800000);
    coinSetthree->setOpen(10861);
    coinSetthree->setHigh(10880);
    coinSetthree->setLow(11190);
    coinSetthree->setClose(10621);


    //Push to series
    coinSeries->append(coinSet);
    coinSeries->append(coinSettwo);
    coinSeries->append(coinSetthree);

    //Push timestamp to categories
    categories << QDateTime::fromMSecsSinceEpoch(1512345600000).toString("dd");
    categories << QDateTime::fromMSecsSinceEpoch(1512259200000).toString("dd");
    categories << QDateTime::fromMSecsSinceEpoch(1512172800000).toString("dd");

    coinSeries->setName("Coin Name");
    coinSeries->setIncreasingColor(QColor(Qt::green));
    coinSeries->setDecreasingColor(QColor(Qt::red));

    QChart *chart = new QChart();
    chart->addSeries(coinSeries);
    chart->setTitle("Coin Name (December 2017)");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->createDefaultAxes();

    QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
    axisX->setCategories(categories);

    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    axisY->setMax(axisY->max() * 1.01);
    axisY->setMin(axisY->min() * 0.99);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);

    //Add widget to main layout
    ui->gridLayout->addWidget(chartView);

    chartView->setRenderHint(QPainter::Antialiasing);
}

CandleStickDialog::~CandleStickDialog()
{
    delete ui;
}
