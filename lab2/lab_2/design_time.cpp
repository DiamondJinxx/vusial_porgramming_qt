#include "design_time.h"
#include "ui_design_time.h"

design_time::design_time(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::design_time)
{
    ui->setupUi(this);
}

design_time::~design_time()
{
    delete ui;
}

void design_time::on_btn_reg_clicked()
{
    QFile xmlfile("run.xml");
    xmlfile.open(QIODevice::WriteOnly);
    //if(xmlfile.isOpen()) this->close();// открывается
    /* FILE *f = fopen("run.xml","w");
    fputs("sdfsdfsdfsd",f);
    fclose(f);
    return ; */
    QXmlStreamWriter xmlWriter(&xmlfile);// создали объект для записи в файл
    if(!xmlfile.isOpen()){
        msg.setText("This file is not open");
        msg.show();
        msg.exec();
    }
    xmlWriter.setAutoFormatting(true); // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();  // Запускаем запись в документ
    xmlWriter.writeStartElement("class");// Записываем первый элемент с его именем,учитываем дальнейшую расширяемость
    xmlWriter.writeStartElement("student"); // тег студента

    /* Здесь следующие строки по 3 создают необходимый тег с его телом */
    xmlWriter.writeStartElement("login");
    xmlWriter.writeCharacters(ui->ln_log->text());
    xmlWriter.writeEndElement();//записываем закрывающий тег

    xmlWriter.writeStartElement("password");
    xmlWriter.writeCharacters(ui->ln_pass->text());
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("surname");
    xmlWriter.writeCharacters(ui->ln_sec_nm->text());
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("year");
    xmlWriter.writeCharacters(ui->ln_year->text());
    xmlWriter.writeEndElement();

   /* закрываем тег студента */
    xmlWriter.writeEndElement();
    /* Закрываем тег класса */
    xmlWriter.writeEndElement();
    /* Завершаем запись в документ */
    xmlWriter.writeEndDocument();
    xmlfile.close();
    this->close();
}
