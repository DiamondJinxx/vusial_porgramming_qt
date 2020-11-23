#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QInputDialog>
#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QPalette>
#include <QPixmap>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QPalette palette;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:

    Ui::Widget *ui;
    int treeCreate(QFile *file, QTreeWidget *, QTreeWidgetItem *); //подсчёт количества элементов в QTreeWidget
    int treeRead(QFile *file, QTreeWidget *); //подсчёт количества элементов в QTreeWidget
    void DeleteItem (QTreeWidgetItem *currentItem); //удаление элемента из QTreeWidget
    void InsertItem (QTreeWidgetItem *, QString); //добавление элемента в QTreeWidget
    int count; //переменная для хранения номера очередного узла
    QTreeWidgetItem *currentItem; //текущий элемент, запоминается при клике в QTreeWidget
    int currentColumn; //номер столбца, на самом деле будет = 0, т.к. у нас 1 столбец
};

#endif // WIDGET_H
