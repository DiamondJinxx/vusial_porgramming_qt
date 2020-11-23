#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
/*
#include <QIntValidator>
#include <QRegExp>
#include <QRegExpValidator>
*/
#include "modelation.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int countItem = 0;
    //QIntValidator *intvalid = new QIntValidator(0,9,this);

signals:
    void sendCount(int count);
     //Modelation *model;

private slots:
    void on_btn_start_clicked();
    void sendCountModelation();

private:
    Ui::MainWindow *ui;
    Modelation *model;
    QMessageBox *msgerr;
};
#endif // MAINWINDOW_H
