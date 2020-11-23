#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

  //  ui->ln_countItem->setValidator(intvalid);

   // connect(ui->btn_start,SIGNAL(clicked),model,SLOT(show));
    model = new Modelation();
    connect(this,SIGNAL(sendCount(int)),model,SLOT(resiveCount(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_start_clicked()
{
    countItem = ui->ln_countItem->text().toInt();
    if(countItem == 0)
    {
        msgerr = new QMessageBox();
        msgerr->setWindowTitle("Ошибка");
        msgerr->setText("Введите число процессоров в моделяции" );
        msgerr->exec();
    }
    else
    {
        sendCountModelation();
        model->show();
    }
}
void MainWindow::sendCountModelation()
{
    emit sendCount(countItem);
}
