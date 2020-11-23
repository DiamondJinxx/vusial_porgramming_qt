#ifndef MODELATION_H
#define MODELATION_H

#include <QWidget>
#include <QMessageBox>
#include <QString>
#include <QList>
#include <QListWidgetItem>
#include <QTimer>
#include <stdlib.h>
#include <time.h>
#include "procces.h"
#include <QtDebug>
//#include <QAbstractItemView>

namespace Ui {
class Modelation;
}

class Modelation : public QWidget
{
    Q_OBJECT
public:
    explicit Modelation(QWidget *parent = nullptr);
    ~Modelation();
    int countProc = 0;
    QMessageBox *msg;
    QTimer timer_boss;// boss's work timer
    QList<Procces*> list_rab;
    Procces * boss = nullptr;
    QListWidgetItem *item;//переменная для привязки элементов к виджету
    QStringList nlst;//список для заноса имен в лист виджет, так как почему-то с нашим списком оно отказывается работать
    //QList<Procces*> init_list(QList<Procces*> lst,int countElem,);
public slots:
   void resiveCount(int count);

private slots:
   void on_btn_stop_clicked();

private:
    Ui::Modelation *ui;
};

#endif // MODELATION_H
