#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "design_time.h"
#include <QtUiTools/QUiLoader>
#include <QLineEdit>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    void open_design_time();
    MainWindow(QWidget *parent = nullptr); // constructor
    ~MainWindow();//destructor
    int sch = 0;

private slots: // why private?

    void on_btn_design_time_clicked();

    void on_btn_run_time_clicked();
    void run_time_check();


private:
    Ui::MainWindow *ui;
    design_time *wind;
    QLineEdit *ln_login;
    QLineEdit *ln_pass;
    QMessageBox msg;

};
#endif // MAINWINDOW_H
