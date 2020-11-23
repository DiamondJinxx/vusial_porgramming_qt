#include "run_time.h"
#include "ui_run_time.h"

run_time::run_time(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::run_time)
{
    ui->setupUi(this);
}

run_time::~run_time()
{
    delete ui;
}
