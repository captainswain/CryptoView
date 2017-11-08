#include "cryptoview.h"
#include "ui_cryptoview.h"

CryptoView::CryptoView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CryptoView)
{
    ui->setupUi(this);
}

CryptoView::~CryptoView()
{
    delete ui;
}
