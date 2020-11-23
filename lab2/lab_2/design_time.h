#ifndef DESIGN_TIME_H
#define DESIGN_TIME_H

#include <QDialog>
#include <QXmlStreamAttribute>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>

namespace Ui {
class design_time;
}

class design_time : public QDialog
{
    Q_OBJECT
    //QDialog *mess;
    QMessageBox msg;

public:
    explicit design_time(QWidget *parent = nullptr);
    ~design_time();

private slots:
    void on_btn_reg_clicked();

private:
    Ui::design_time *ui;
};

#endif // DESIGN_TIME_H
