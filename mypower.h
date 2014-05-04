#ifndef MYPOWER_H
#define MYPOWER_H

#include <QObject>

class QString;
class QTimer;

class myPower : public QObject
{
    Q_OBJECT
public:
    explicit myPower(QObject *parent = 0);
    void InitXml();


    QTimer *timer;
signals:

public slots:
    void ReadXml();
};

#endif // MYPOWER_H
