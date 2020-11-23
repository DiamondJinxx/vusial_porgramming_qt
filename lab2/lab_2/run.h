#ifndef RUN_H
#define RUN_H

#include <QWidget>
#include <QXmlStreamAttribute>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QTextEdit>

namespace Ui {
class run;
}

class run : public QWidget
{
    Q_OBJECT

public:
    QTextEdit *ln_login;
    QTextEdit *ln_pass;
    explicit run(QWidget *parent = nullptr);
    ~run();

private slots:
    void on_btn_signin_clicked();

private:
    Ui::run *ui;
};

#endif // RUN_H
