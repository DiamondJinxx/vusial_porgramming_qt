#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QApplication>
#include <QtMath>

//const for moving lbl_clock
#define ROOT_2  sqrtf(2)
#define STEP  3.14/60
#define PI    3.14
#define A 200

//clock pos
#define CLK_X  300
#define CLK_Y  300

double _sin_q = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    //Выводим значение времени в начале работы для устранения отсутствия времени до первого срабатывания таймера
    ui->lbl_clock->setText(QTime::currentTime().toString());
    timer_clk = new QTimer;
    timer_lmkt = new QTimer;
    //Связываем сигнал переполнения таймера со слотом
    connect(timer_clk, SIGNAL(timeout()), SLOT(timer_overflow())); //this,
    //Задаем время срабатывания таймера (в мс)
    timer_clk->start(1000);
    timer_lmkt->start(65);
    ui->spin_test->setRange(0, 150);
    ui->sliderH->setRange(0, 150);
    ui->sliderV->setRange(0, 150);
    connect(ui->spin_test,SIGNAL(valueChanged(int)),ui->sliderH,SLOT(setValue(int)));
    connect(ui->sliderH,SIGNAL(valueChanged(int)),ui->spin_test,SLOT(setValue(int)));
    connect(ui->spin_test,SIGNAL(valueChanged(int)),ui->sliderV,SLOT(setValue(int)));
    connect(ui->sliderV,SIGNAL(valueChanged(int)),ui->spin_test,SLOT(setValue(int)));
    connect(ui->btn_quite,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->mnu_act_close,SIGNAL(triggered()),this,SLOT(close()));
    connect(timer_lmkt, SIGNAL(timeout()), this, SLOT(leminiskata()));
    //связать с таймром и отдбельной функцией изменять позицию,функция прописать в хедере
   /* for(int x = 0;x<=100;x+=5){
        //ui->lbl_clock->`
        ui->lbl_clock->move(ui->lbl_clock->pos().x()+5,ui->lbl_clock->pos().y()+5); //pos().x()+x;
    } */
}
//Следующий метод (слот) вызывется при каждом переполнении таймера
void MainWindow::timer_overflow()
{
    //Обновляем значение времени на форме
    ui->lbl_clock->setText(QTime::currentTime().toString());
}
void MainWindow::leminiskata()
{   /*добавляем статично заданные координаты часов, так как если вызывать их
      через метод pos(), то вызываются координаты, которые изменились в прошлую
    итерацию таймера, в итоге часы описывают дугу,а не леминискату;
    таким образом мы смещаем центр симметрии леминискаты*/
    static double _phi = 0;
    _sin_q = pow( sin(_phi), 2) + 1;
    double new_x = A * ROOT_2 * cos(_phi) / _sin_q + CLK_X;
    double new_y = A * ROOT_2 * cos(_phi) * sin(_phi) / _sin_q + CLK_Y;
    ui->lbl_clock->move((int)new_x, (int)new_y);

    _phi += STEP;
    if( _phi >= PI * 2 + STEP) _phi = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

