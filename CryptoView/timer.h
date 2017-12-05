#ifndef TIMER_H
#define TIMER_H

#include <QObject>

class timer : public QObject
{
    Q_OBJECT
public:
    explicit timer(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TIMER_H