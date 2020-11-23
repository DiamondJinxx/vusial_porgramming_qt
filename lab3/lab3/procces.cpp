#include "procces.h"

Procces::Procces(QString n,int b, int t)
{
    big_boss = b;
    name = n;
    tmr_voice = new QTimer();
    tmr_voice->setInterval(t * 1000);
}
