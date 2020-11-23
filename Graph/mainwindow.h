#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QStringListModel>
#include <QTableView>
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QVector>

#include <QtCharts/QChart>
#include <QtCharts/QtCharts>
#include <QPainter>

//using namespace QtCharts;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStandardItemModel *modelOut=NULL;
    int all=0, t=0, time=0, moneycurrent=0, moneyBefore=0, num=1;
    QVector<int> begin;//
    QVector<int> money;//вектор для значений сумм

private:
    Ui::MainWindow *ui;
    QStringListModel *modelIn;
    QChartView *chartView;
    QPainter *painter;
    QLineSeries *series;
    QChart *chart;
    QStandardItemModel *modelCurrent,  *modelInDrink;
    QTimer *timer1, *timer2, *timeChoseFilling, *timeWait;
    QPalette palette;
    bool timerstatus=false, finish=false, graf1=false, hide = false;
    int people=0,  sec=0, timein[11];
    float choseTime=0;
    QModelIndex index2;
private slots:          //слоты для работы таймеров
    void updateList();
    void updateGraf();
    void updateList2();
    void action()
    { QMessageBox::StandardButton reply=QMessageBox::question(this, "Выход", "Вы точно хотите выйти?", QMessageBox::Yes| QMessageBox::No);
        if(reply == QMessageBox::Yes) {close();} }
    void full() {showFullScreen();}
    void normal() {showNormal();}
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    //void drawLabel(QPaintEvent *e);
    void on_pushButton_3_clicked();
};
#endif // MAINWINDOW_H
