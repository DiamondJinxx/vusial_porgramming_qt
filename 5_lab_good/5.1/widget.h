#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QtWidgets>
#include <QFile>
#include <QDir>

namespace Ui { class Widget; }
class Widget : public QWidget {
    Q_OBJECT
    Ui::Widget *ui;
public:
    Widget(QWidget *parent = 0);
    void updateActions(); //слот для обновления состояния кнопок

    bool load(QString); //десериализация или просто считывание из файла данных дерева
    bool save(); //сериализация или перевод структуры данных (дерево) в последовательность битов
    bool deleteTree();
    QModelIndex rec(const QModelIndex &parent, QFile& file);
    //QStringList obhod_dereva(QModelIndex, uint);
private slots: //слоты для действий, выполняемых по кнопкам
    void insertChild();
    void insertRow();
    void removeRow();

    void on_load_clicked();
    void on_save_clicked();
    void on_Ok_clicked();
    void on_Cancel_clicked();

public slots:
    void updateActionButtons();
};
#endif // WIDGET_H
