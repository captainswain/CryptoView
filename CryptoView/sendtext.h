#ifndef SENDTEXT_H
#define SENDTEXT_H

#include <QObject>

class sendText : public QObject
{
    Q_OBJECT
public:
    explicit sendText(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SENDTEXT_H