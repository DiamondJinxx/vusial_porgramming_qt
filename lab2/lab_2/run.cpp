#include "run.h"
#include "ui_run.h"

run::run(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::run)
{
    ui->setupUi(this);
   // ln_login = this->findChild<QTextEdit*>("ln_login");
    //ln_pass = this->findChild<QTextEdit*>("ln_pass");
}

run::~run()
{
    delete ui;
}

void run::on_btn_signin_clicked()
{
    QFile xmlfile("run.xml");
    xmlfile.open(QIODevice::ReadOnly);
    QXmlStreamReader xml(&xmlfile);
    xml.readNext();// прыгаем на след строчку
    while (!xml.isEndElement()) { // пока не последний тег
        if (xml.isStartElement()) {

            QString name;
            while (xml.name().toString() != "login") {
                xml.readNext();
            }
            while (xml.name().toString() != "password") {
                xml.readNext();
            }
            //l->name = xml.readElementText();
            while (xml.name().toString() != "mode") {
                xml.readNext();
            }
        // }
            char mode = xml.readElementText()[0] == '1';
            while (xml.name().toString() != "arg") {
             xml.readNext();
            }
           // l->arg = xml.readElementText();
          /*  if (mode) {
                x = new QPushButton(scrollArea);
                x->setText(l->name);
                x->setGeometry(0, i * x->height() + 1, scrollArea->width() - 5, x->height());
                connect(x, SIGNAL(clicked()), this, SLOT(runApp()));
                x->show();
            } else {
                comboBox->addItem(l->name);
          }*/
            continue;
        }
     xml.readNext();
    }
    xmlfile.close();

}
