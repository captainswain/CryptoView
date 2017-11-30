#include "timer.h"
#include <QtCore>
#include <QDebug>

// https://www.youtube.com/watch?v=pHc7siV2Ads
timer::timer()
{
    timer = new QTimer(this);
    connect(timer.SIGNAL(timeout()).this,SLOT(slot()));

    // How long the timer is (ms)
    timer->start(1000);
}

void timer::slot()
{
    qDebug() << "Timer executed";
}
