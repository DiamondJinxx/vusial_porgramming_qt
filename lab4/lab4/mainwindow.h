#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QStringListModel>
#include <QTableView>
#include <QAbstractItemView>
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QInputDialog>
#include <QPixmap>
#include <QtCharts>
//#include <QtCharts/QLogValueAxis>
//#include <QtCharts/QLineSeries>
//#include <QtCharts/QValueAxis>
//#include <QtCharts/QChartView>
#include <time.h>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStringListModel *modelIn, *modelInDrink;
    QStandardItemModel *modelOut;
    QStandardItemModel *modelCurrent;
    QTimer *timer1, *timeChoseFilling, *timeWait,*timerGraph;  //таймер
    QPalette palette;
    bool timerstatus=false, finish=false;    //поле, хранящее информацию о срабатывании временного однократного таймера
    int t=0, people=0, all=0, sec=0, timein[11];
    int profit = 0;
    QList<int> drink_prices;// список стоймостей напитк за 100мл
    QChartView *chartView = new  QChartView(this); // представление для графика
    QLineSeries *series = new QLineSeries();
    float choseTime=0,x_time = 0;
    QModelIndex index2;
private slots:          //слоты для обработки таймеров
    void updateList();
    void updateList2();
    void action()
    { QMessageBox::StandardButton reply=QMessageBox::question(this, "Выход", "Вы точно хотите выйти?", QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes) {close();} }
    void full() {showFullScreen();}
    void normal() {showNormal();}
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};
#endif // MAINWINDOW_H
