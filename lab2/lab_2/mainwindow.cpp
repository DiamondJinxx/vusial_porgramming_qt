#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // connect(ui->btn_design_time,SIGNAL(clicked()),dt_window,open_design_time());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::open_design_time() //  зачем мы расширяем область видимости?
{

}

void MainWindow::on_btn_design_time_clicked()//еммит; событие связывает через класс сигнл и слот
{
   // connect(&ui->btn_run_time, clicked, this, open_design_time);
    /* design_time dt_window;
    dt_window.setModal(true);// modal window; change?
    dt_window.exec(); */
    wind = new design_time(this);
    wind->show();

}

void MainWindow::on_btn_run_time_clicked()
{
         /* выгрузка лоудером страницы с run_time.ui
            как сформировать обработку нажатия кнопки?
*/
    QFile file("run.ui");
    file.open(QIODevice::ReadOnly);
    QUiLoader x;
    QWidget* form = x.load(&file);
    QPushButton* btn_signin = form->findChild<QPushButton*>("btn_signin");
    assert(btn_signin);
 /*   ln_login = form->findChild<QLineEdit*>("ln_login");
    ln_pass = form->findChild<QLineEdit*>("ln_pass");
    connect(btn_signin, SIGNAL(clicked()), this, SLOT(run_time_check()));
   // scrollArea = form->findChild<QScrollArea*>("scrollArea");
   // comboBox = form->findChild<QComboBox*>("comboBox");
    *///form->setAttribute(Qt::WA_DeleteOnClose);// удаелние при нажатии на крестик
    //connect(form, SIGNAL(destroyed(QObject*)), this, SLOT(close())); // закрытие основного с закрытием побочного
    //init();
    form->show();
    file.close();
}

void MainWindow::run_time_check(){
        QFile xmlfile("run.xml");
        xmlfile.open(QIODevice::ReadOnly);
        QXmlStreamReader xml(&xmlfile);
        xml.readNext();// прыгаем на след строчку
        while (!xml.isEndElement()) { // пока не последний тег
            if (xml.isStartElement()) {

                QString login,pass;
                while (xml.name().toString() != "student") {
                    xml.readNext();
                }
                while (xml.name().toString() != "login") {
                    xml.readNext();
                }
                login = xml.readElementText();
                while (xml.name().toString() != "password") {
                    xml.readNext();
                }
                pass = xml.readElementText();
            // }

                if(login == ln_login->text() && pass == ln_pass->text()){
                    sch++;
                    QString str = QString::number(3 - sch);
                    if(sch<=3){
                        msg.setText("Вход успешно выполнен.Осталось попыток " + str);
                        msg.show();
                        msg.exec();
                    }else {
                        msg.setText("Вы исчерпали количество попыток");
                        msg.show();
                        msg.exec();
                        xml.readNext();
                        xmlfile.close();
                        return ;
                    }
                 }else {
                    if(login != ln_login->text()){
                        msg.setText("Неверный логин или пороль");
                        msg.show();
                        msg.exec();
                    }
                 }
                continue;
            }


            xml.readNext();
        }


        xmlfile.close();

}
