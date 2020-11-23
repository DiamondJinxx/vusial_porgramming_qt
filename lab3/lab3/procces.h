#ifndef PROCCES_H
#define PROCCES_H

#include <QTimer>
//#include <QString>
class Procces
{
public:
    Procces(QString n,int boss,int time);
    int big_boss = 0;
    QTimer *tmr_voice;//boss work's timer
    char crash = 0;
    QString name;

    //timeout почитать
};

#endif // PROCCES_H
