#include "cryptoview.h"
#include "ui_cryptoview.h"

CryptoView::CryptoView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CryptoView)
{
    ui->setupUi(this);
    this->LoadValues();
}

CryptoView::~CryptoView()
{
    delete ui;
}

void CryptoView::on_addCurrencyBtn_clicked()
{
    ui->label_11->setText("Hello");
}
//void CryptoView::updatelabel(Currency current, ){
//    //label_11->setText("test!");
//    //ui->statusLabel->setText(str);

//}

void CryptoView::LoadValues(){

    // This is ran when the form is constructed
    // Imagine form.load in VS
}
