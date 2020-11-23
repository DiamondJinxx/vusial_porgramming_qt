#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Выводим значение времени в начале работы для устранения отсутствия времени до первого срабатывания таймера
    ui->label->setText(QTime::currentTime().toString());

    timer = new QTimer;

    //Связываем сигнал переполнения таймера со слотом
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timer_overflow()));

    //Задаем время срабатывания таймера (в мс)
    timer->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Следующий метод (слот) вызывется при каждом переполнении таймера
void MainWindow::timer_overflow()
{
    //Обновляем значение времени на форме
    ui->label->setText(QTime::currentTime().toString());
}
