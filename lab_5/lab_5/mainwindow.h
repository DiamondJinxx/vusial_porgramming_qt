#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_btn_add_clicked();

    void on_btn_del_clicked();

private:
    Ui::MainWindow *ui;
    int treeCount(QTreeWidget *, QTreeWidgetItem *); // подсчет количества элемента в дереве
    void deleteItem(QTreeWidgetItem *currentItem); // удаление элемента
    void insertItem(QTreeWidgetItem *, QString); // добавление элемента
    void showAll(void); //вывод информации о виджете дерева
    int count; // переменная хранения номера очередног узла
    QTreeWidgetItem *currentItem; // текущий элемент, который запоминается при клике на эелемент
    int currentColumn; // номер столбца, но на самом деле столбец у нас лишь 1
};
#endif // MAINWINDOW_H
