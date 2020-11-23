#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QtMath>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   QPixmap bckgnd(":/img/drink.jpg");
   bckgnd = bckgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
   palette.setBrush(QPalette::Background,bckgnd);
   this->setPalette(palette);
   timerstatus=false;
   modelIn = new QStringListModel(this);
   modelInDrink = new QStandardItemModel( 1, 2, this);
   modelCurrent = new QStandardItemModel( 1, 3, this);
   modelOut = new QStandardItemModel( 1, 5, this);
   modelOut->setHeaderData(0,Qt::Horizontal,"Клиент");
   modelOut->setHeaderData(1,Qt::Horizontal,"Объем");
   modelOut->setHeaderData(2,Qt::Horizontal,"Время в очереди");
   modelOut->setHeaderData(3,Qt::Horizontal,"Время раздумий");
   modelOut->setHeaderData(4,Qt::Horizontal,"Сумма покупки");
   modelCurrent->setHeaderData(0,Qt::Horizontal,"Напиток");
   modelCurrent->setHeaderData(1,Qt::Horizontal,"Объем");
   modelCurrent->setHeaderData(2,Qt::Horizontal,"Стоймость");
   QMenu *menu = menuBar()->addMenu("Основное");
   QMenu *size = menu->addMenu("Вид");
   QAction *full = new QAction( tr("Полноэкранный"), this);
   QAction *normal = new QAction( tr("Оконный"), this);
   size->addAction(full);
   size->addAction(normal);
   QAction *close = new QAction(tr("Закрыть"), this);
   menu->addAction(close);
   connect( close, SIGNAL(triggered()), this, SLOT(action()));
   connect( full, SIGNAL(triggered()), this, SLOT(full()));
   connect( normal, SIGNAL(triggered()), this, SLOT(normal()));
   close->setShortcut(tr("Esc"));
   full->setShortcut(tr("Ctrl++"));
   normal->setShortcut(tr("Ctrl+-"));
   //Подключение моделей
   ui->ListInClient->setModel(modelIn);
   ui->ListInDrink->setModel(modelInDrink);
   ui->ListCurrent->setModel(modelCurrent);
   ui->ListOut->setModel(modelOut);
   //Запрещает прямое редактирование списка
   ui->ListInClient->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->ListInDrink->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->ListCurrent->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->ListOut->setEditTriggers(QAbstractItemView::NoEditTriggers);
   timer1= new QTimer(this);
   timer2= new QTimer(this);
   timeWait= new QTimer(this);
   timeChoseFilling= new QTimer(this);
   timer1->setInterval(1000); timer2->setInterval(1000);
   connect( timer1, SIGNAL(timeout()), this, SLOT(updateList()));
   connect( timer2, SIGNAL(timeout()), this, SLOT(updateGraf()));
   connect( timeChoseFilling, SIGNAL(timeout()), this, SLOT(updateList2()));
   timer1->start(); timer2->start();
   //modelInDrink->insertRows(0, 1);
   QModelIndex drink = modelInDrink->index(0,0);
   QModelIndex value = modelInDrink->index(0,1);
   modelInDrink->setData( drink, "Cola");
   modelInDrink->setData( value, "30");
   begin.resize(num); money.resize(num);
   begin[0]=0; money[0]=0;
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::updateList()
{
    ++time;
    int j = qrand() % 3;
    for(int i=0; i<=people; i++)
        timein[i]++;
    int drinkVolume=0, chose=0, drinkindex=0;
    QModelIndex indexCurrent = modelIn->index(0);
    QModelIndex Drink = modelCurrent->index( 0, 0, QModelIndex());
    QModelIndex DrinkValue = modelCurrent->index( 0, 1, QModelIndex());
    QModelIndex DrinkCost = modelCurrent->index( 0, 2, QModelIndex());
    if(finish==true)
    {
        finish=false;
        modelOut->insertRows(t,1);
        QModelIndex indexCurrent1 = modelCurrent->index( t, 0, QModelIndex());
        QModelIndex Drink1 = modelOut->index( t, 0, QModelIndex());
        QModelIndex DrinkValue1 = modelOut->index( t, 1, QModelIndex());
        QModelIndex TimeinQueue1 = modelOut->index( t, 2, QModelIndex());
        QModelIndex TimeChose1 = modelOut->index( t, 3, QModelIndex());
        QModelIndex DrinkCost1 = modelOut->index( t, 4, QModelIndex());
        modelOut->setData( indexCurrent1, modelCurrent->data(indexCurrent));
        modelOut->setData( Drink1, modelCurrent->data(Drink));
        modelOut->setData( DrinkValue1, modelCurrent->data(DrinkValue));
        modelOut->setData( TimeinQueue1, QString::number(fabs( timein[0] - choseTime / 1000)));
        modelOut->setData( TimeChose1, QString::number( choseTime / 1000));
        modelOut->setData( DrinkCost1, modelCurrent->data(DrinkCost));
        t++;
        modelCurrent->setData( indexCurrent, QString());
        modelCurrent->setData( Drink, QString());
        modelCurrent->setData( DrinkValue, QString());
        modelCurrent->setData( DrinkCost, QString());

    }
    else if(modelIn->rowCount() && !timerstatus)
    {
        timerstatus = true;
        drinkVolume = qrand() % 3;
        switch(drinkVolume)
        {
            case 0: drinkVolume = 300; break;
            case 1: drinkVolume = 400; break;
            case 2: drinkVolume = 500; break;
        }
        chose = qrand() % 5000;
        drinkindex = qrand() % modelInDrink->rowCount();
        modelCurrent->setData( indexCurrent, modelIn->index(0));
        modelCurrent->setData( Drink, modelInDrink->data( modelInDrink->index( drinkindex,0)));
        int cost=modelInDrink->data( modelInDrink->index( drinkindex,1)).toInt()*drinkVolume/100;
        num++;
        begin.resize(num); money.resize(num);
        begin[num-1]=time; money[num-1]=money[num-2]+cost;
        moneyBefore = moneycurrent;
        moneycurrent += cost;
        modelCurrent->setData( DrinkValue, QString::number( drinkVolume));
        modelCurrent->setData( DrinkCost, QString::number( cost));
        modelIn->removeRows(0,1);
        timeChoseFilling->setInterval( chose + drinkVolume * 20);
        timeChoseFilling->start();
        for( int i=0; i < 10; i++)
            timein[i] = timein[i+1];
        people--;
    }
}

void MainWindow::updateList2()
{
    timerstatus = false;
    finish = true;
    timeChoseFilling->stop();
    choseTime = timeChoseFilling->interval();
}

void MainWindow::updateGraf()
{
    if(num>=2 && hide)
    {
        int t=time;
        int i=1;
        bool beg=false;//проход ступеньки
        //QMessageBox::warning(this, "3Значение t", QString::number(t));
        if(graf1) { ui->horizontalLayout->removeWidget(chartView); chart->removeAllSeries();}


        chartView = new QChartView(this);// Создаётся представление для графика

        graf1 = true;
        ui->horizontalLayout->addWidget(chartView);
        series = new QLineSeries();    //Создаётся серия значений для графика
        int k = 0;
        k++;
        while (k < t)
        {
            ++k;
            if(k==begin[i])
            {
                int mon=money[i-1];
                while(mon < money[i])
                {
                    *series << QPointF(k, mon);
                    mon+=1;
                }
                beg = true;
            }
            if(i<num-1 && beg) { i++; beg = false; *series << QPointF(k, money[i-1]);}
            else if(beg) *series << QPointF(k, money[i]);
            else *series << QPointF(k, money[i-1]);

        }

        // Создаётся график и добавляется в него серия значений
        chart = new QChart();
        chart->addSeries(series);
        chart->legend()->hide();        //Серия всего одна на графике, так что легенда не нужна
        chart->setTitle("Прибиль автомата");

        // Настраиваются оси графика
        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("₽, рублей");            //Подпись к оси Y
        axisY->setLabelFormat("%.2f");
        axisY->setTickCount(5);                 //Сколько отрезков на оси, минимум 2
        chart->addAxis(axisY, Qt::AlignLeft); //Подключение оси к графику
        series->attachAxis(axisY);              //Подключение оси к значениям

        QValueAxis *axisX = new QValueAxis();
        axisX->setTitleText("t, секунд");
        axisX->setLabelFormat("%.2f");
        axisX->setTickCount(5);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);
        axisY->setRange(0, moneycurrent+10);
        chartView->setChart(chart);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(people<=10)
    {
        modelIn->insertRows( people, 1);
        index2 = modelIn->index( people);
        modelIn->setData( index2, QString::number( ++all ));
        timein[people] = 0;
        people++;
    }
    else
        QMessageBox::information( this, "Да ну нафиг", "Слишком большая очередь");
}

void MainWindow::on_pushButton_2_clicked()
{
    bool ok1, ok2;
    int val;
    QString str = QInputDialog::getText( 0, "Введите напиток", "Название:", QLineEdit::Normal, "Cola", &ok1);
    val = QInputDialog::getInt(0,"Введите цену", "Цена", 30 , 1, 50, 1, &ok2);
    if (ok1 && ok2)
    {
        int row = modelInDrink->rowCount();
        modelInDrink->insertRows( row, 1);
        QModelIndex drink = modelInDrink->index( row, 0);
        modelInDrink->setData( drink, str);
        QModelIndex value = modelInDrink->index( row, 1);
        modelInDrink->setData( value, QString::number(val));
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    hide=true;
}
