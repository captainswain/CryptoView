#ifndef CANDLESTICKDIALOG_H
#define CANDLESTICKDIALOG_H

#include <QDialog>
#include <QCandlestickSeries>
#include <QChartView>
#include <QValueAxis>
#include <QDateTime>
#include <QApplication>
#include <QMainWindow>


namespace Ui {
class CandleStickDialog;
}

class CandleStickDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CandleStickDialog(QWidget *parent = 0);
    ~CandleStickDialog();

private:
    Ui::CandleStickDialog *ui;
};

#endif // CANDLESTICKDIALOG_H
