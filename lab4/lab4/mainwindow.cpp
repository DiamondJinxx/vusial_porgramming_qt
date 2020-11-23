#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QtMath>
MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   //QT_INIT_RESOURCE(resource);
   QPixmap bckgnd(":/img/drink.jpg");

   ui->HlGraph->addWidget(chartView);
   bckgnd = bckgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
   palette.setBrush(QPalette::Background,bckgnd);
   this->setPalette(palette);
   timerstatus=false;
   //неудачная попытка расширить столбцы в зависимости от названия, возможно метод орентирован не от ширины заоголвка
  // ui->ListOut->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
  // ui->ListOut->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
   modelIn = new QStringListModel(this);
   modelInDrink = new QStringListModel(this);
   modelCurrent = new QStandardItemModel( 1, 2, this);
   modelOut = new QStandardItemModel( 1, 4, this);
   modelOut->setHeaderData(0,Qt::Horizontal,"Клиент");
   modelOut->setHeaderData(1,Qt::Horizontal,"Объем");
   modelOut->setHeaderData(2,Qt::Horizontal,"Время в очереди");
   modelOut->setHeaderData(3,Qt::Horizontal,"Время раздумий");
   modelCurrent->setHeaderData(0,Qt::Horizontal,"Напиток");
   modelCurrent->setHeaderData(1,Qt::Horizontal,"Объем");

   //объявление графика, не работает
  // QChartView *charView = new QChartView();

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
   ui->ListIn->setModel(modelIn);
   ui->ListInDrink->setModel(modelInDrink);
   ui->ListCurrent->setModel(modelCurrent);
   ui->ListOut->setModel(modelOut);
   //Запрещает прямое редактирование списка
   ui->ListIn->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->ListInDrink->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->ListCurrent->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->ListOut->setEditTriggers(QAbstractItemView::NoEditTriggers);
   timer1= new QTimer(this);
   timeWait= new QTimer(this);
   timeChoseFilling= new QTimer(this);
   timer1->setInterval(1000);
   connect( timer1, SIGNAL(timeout()), this, SLOT(updateList()));
   connect( timeChoseFilling, SIGNAL(timeout()), this, SLOT(updateList2()));
   timer1->start();
   modelInDrink->insertRows(0, 1);// вставка в модель одной строки
   QModelIndex drink = modelInDrink->index(0);
   modelInDrink->setData( drink, "Coffee");
   drink_prices.append(20);
   ui->label_4->setText(drink.data(Qt::DisplayRole).toString());
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::updateList()
{
    int j = qrand() % 3;
    for(int i = 0; i <= people; i++)
        timein[i]++;
    int drinkVolume = 0, chose = 0, drinkindex = 0;
    QModelIndex indexCurrent = modelIn->index(0);
    QModelIndex Drink = modelCurrent->index( 0, 0, QModelIndex());
    QModelIndex DrinkValue = modelCurrent->index( 0, 1, QModelIndex());
    if(finish == true)
    {
        finish = false;
        modelOut->insertRows(t,1);
        QModelIndex indexCurrent1 = modelCurrent->index( t, 0, QModelIndex());
        QModelIndex Drink1 = modelOut->index( t, 0, QModelIndex());
        QModelIndex DrinkValue1 = modelOut->index( t, 1, QModelIndex());
        QModelIndex TimeinQueue1 = modelOut->index( t, 2, QModelIndex());
        QModelIndex TimeChose1 = modelOut->index( t, 3, QModelIndex());
        modelOut->setData( indexCurrent1, modelCurrent->data(indexCurrent));
        modelOut->setData( Drink1, modelCurrent->data(Drink));
        modelOut->setData( DrinkValue1, modelCurrent->data(DrinkValue));
        //как форматировать запись, чтобы вывод был не в экспоненциальной?
        modelOut->setData( TimeinQueue1, QString::number(fabs( timein[0] - choseTime / 1000)));
        modelOut->setData( TimeChose1, QString::number( choseTime / 1000));
        t++;
        modelCurrent->setData( indexCurrent, QString());
        modelCurrent->setData( Drink, QString());
        modelCurrent->setData( DrinkValue, QString());

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
        modelCurrent->setData( Drink, modelInDrink->data( modelInDrink->index( drinkindex)));
        modelCurrent->setData( DrinkValue, QString::number( drinkVolume));
        modelIn->removeRows( 0, 1);
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
    x_time +=choseTime;
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
    bool ok;
    QString str = QInputDialog::getText( nullptr, "Введите напиток", "Название:", QLineEdit::Normal, "Cola", &ok);
    int price = QInputDialog::getInt(nullptr,"Стоймость напитка","Повелитель, сколько стоит напиток?",20,0,50);
    if (ok)
    {
        int row = modelInDrink->rowCount();
        modelInDrink->insertRows( row, 1);
        QModelIndex drink = modelInDrink->index( row);
        modelInDrink->setData( drink, str);
        drink_prices.append(price);
    }
    ui->label_4->setText(QString::number(drink_prices.last()));
}
