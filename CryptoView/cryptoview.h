#ifndef CRYPTOVIEW_H
#define CRYPTOVIEW_H

#include <QMainWindow>

namespace Ui {
class CryptoView;
}

class CryptoView : public QMainWindow
{
    Q_OBJECT

public:
    explicit CryptoView(QWidget *parent = 0);
    ~CryptoView();

private:
    Ui::CryptoView *ui;
};

#endif // CRYPTOVIEW_H
