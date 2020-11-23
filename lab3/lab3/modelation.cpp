#include "modelation.h"
#include "ui_modelation.h"
#include "procces.h"

Modelation::Modelation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Modelation)
{
    ui->setupUi(this);

}

Modelation::~Modelation()
{
    delete ui;
}
void Modelation::resiveCount(int count)
{
    if(count == 0)
    {
        msg = new QMessageBox();
        msg->setWindowTitle("Ошибка");
        msg->setText("Количество процессов 0");
        msg->exec();
    }
    else
    {
        srand(time(0));// Выставляем рандомное время time(0) - текущее время
        for(int i = 0; i < countProc; i++){
            list_rab.append(new Procces("process" + QString::number(i),0, rand()%40+10));
        }
        int bi = rand()%(countProc-1);
        for(QList<Procces*>::iterator it = list_rab.begin();it != list_rab.end(); it ++)
        {
            bi--;
            if(!bi)
            {
                (*it)->big_boss = 1;
                boss = *it;
                list_rab.erase(it);
                break;
            }
        }
        ui->listWidget_output->setSelectionMode(QAbstractItemView::MultiSelection);//включение режима выделение несокльких элементов
        ui->listWidget_output->setViewMode(QListView::IconMode);
        foreach (Procces *lst, list_rab) {
            item = new QListWidgetItem(lst->name,ui->listWidget_output);
            item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsDragEnabled);
        }
        if(countProc > 0) ui->label_2->setText(list_rab[2]->name);
    }
    countProc = count;
    QString str = QString::number(countProc);
    ui->label->setText(str);
}

void Modelation::on_btn_stop_clicked()
{

}
