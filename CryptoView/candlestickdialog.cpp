#include "candlestickdialog.h"
#include "ui_candlestickdialog.h"

CandleStickDialog::CandleStickDialog(QString symbol, QWidget *parent) :
    m_symbol(symbol),
    QDialog(parent),
    ui(new Ui::CandleStickDialog)
{
    ui->setupUi(this);

    m_webSocket = new QWebSocket();
    connect(m_webSocket, &QWebSocket::connected, this, &CandleStickDialog::onConnected);
    connect(m_webSocket, &QWebSocket::sslErrors, this, &CandleStickDialog::onSslErrors);
    connect(m_webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &CandleStickDialog::onError);
    m_webSocket->open(QUrl("wss://api.bitfinex.com/ws/2"));

    m_coinSeries = new QCandlestickSeries(this);
    m_coinSeries->setName(symbol);
    m_coinSeries->setIncreasingColor(QColor(Qt::green));
    m_coinSeries->setDecreasingColor(QColor(Qt::red));

    m_chart = new QChart();
    m_chart->addSeries(m_coinSeries);
    m_chart->setTitle("Coin Name (December 2017)");
    m_chart->setAnimationOptions(QChart::SeriesAnimations);
    m_chart->createDefaultAxes();

    axisX = qobject_cast<QBarCategoryAxis *>(m_chart->axes(Qt::Horizontal).at(0));
    axisX->setCategories(m_categories);

    axisY = qobject_cast<QValueAxis *>(m_chart->axes(Qt::Vertical).at(0));
    axisY->setMax(axisY->max() * 1.01);
    axisY->setMin(axisY->min() * 0.99);

    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);

    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    //Add widget to main layout
    ui->gridLayout->addWidget(m_chartView);
}

void CandleStickDialog::open(const QUrl &url)
{
    m_webSocket->open(QUrl(url));
}

CandleStickDialog::~CandleStickDialog()
{
    delete ui;
}

void CandleStickDialog::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &CandleStickDialog::onTextMessageReceived);
    m_webSocket->sendTextMessage("{\"event\":\"subscribe\",\"channel\":\"candles\",\"key\":\"trade:1h:t" + m_symbol + "USD\"}");
}

void CandleStickDialog::onTextMessageReceived(QString message)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    if (jsonDoc.isEmpty() || jsonDoc.isNull())
        return;

    if (jsonDoc.isArray())
    {
        QJsonArray arr = jsonDoc.array();

        // Drop heartbeat message
        if (arr.at(1).toString() == "hb")
            return;

        QJsonArray data = arr.at(1).toArray();

        if (data.size() > 6)
        {
            // We got initial data do some more parsing
            foreach (const QJsonValue & value, data) {
                QJsonArray candle = value.toArray();

                qreal timestamp = candle.at(0).toDouble();

                QCandlestickSet *coinSet = new QCandlestickSet(timestamp);
                coinSet->setOpen(candle.at(1).toDouble());
                coinSet->setClose(candle.at(2).toDouble());
                coinSet->setHigh(candle.at(3).toDouble());
                coinSet->setLow(candle.at(4).toDouble());
                m_coinSeries->append(coinSet);
                qDebug() << candle.at(3).toDouble();

                //Push timestamp to categories
                m_categories << QDateTime::fromMSecsSinceEpoch(timestamp).toString("dd");
                if (axisY->max() < candle.at(3).toDouble()) axisY->setMax(candle.at(3).toDouble());
                if (axisY->min() < candle.at(4).toDouble()) axisY->setMin(candle.at(4).toDouble());
            }
        }
        else if (data.size() == 6)
        {
            // We got an update for one candle
        }
        //qDebug() << "Axis Y: " << m_chart->axes(Qt::Vertical).size();
        //qDebug() << "Axis Y:" << qobject_cast<QValueAxis *>(m_chart->axes(Qt::Vertical).at(0))->max() * 1.01;

        axisX->categories().clear();
        axisX->setCategories(m_categories);

        axisY->setMax(qobject_cast<QValueAxis *>(m_chart->axes(Qt::Vertical).at(0))->max() * 1.01);
        axisY->setMin(qobject_cast<QValueAxis *>(m_chart->axes(Qt::Vertical).at(0))->min() * 0.99);
    }
}

void CandleStickDialog::onSslErrors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors);

    // WARNING: Never ignore SSL errors in production code.
    // The proper way to handle self-signed certificates is to add a custom root
    // to the CA store.
    // TODO: Handle SSL errors

    m_webSocket->ignoreSslErrors();
}

void CandleStickDialog::onError(QAbstractSocket::SocketError error)
{
    qDebug() << m_webSocket->errorString();
}
