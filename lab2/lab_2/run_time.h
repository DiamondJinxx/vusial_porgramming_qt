#ifndef RUN_TIME_H
#define RUN_TIME_H

#include <QDialog>

namespace Ui {
class run_time;
}

class run_time : public QDialog
{
    Q_OBJECT

public:
    explicit run_time(QWidget *parent = nullptr);
    ~run_time();

private:
    Ui::run_time *ui;
};

#endif // RUN_TIME_H
