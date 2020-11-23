#include "widget.h"
#include "tree.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>
#include <QSize>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
 ui->setupUi(this);
 ui->label->hide();
 ui->lineEdit-> hide();
 ui->Ok->hide();
 ui->Cancel->hide();
 if (!load("plants.txt")) {
     connect(ui->treeView->selectionModel(),SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)),
             this, SLOT(updateActionButtons()));
     connect(ui->insertRowAction,SIGNAL(clicked()),this,SLOT(insertRow()));
     connect(ui->removeRowAction,SIGNAL(clicked()),this,SLOT(removeRow()));
     connect(ui->insertChildAction,SIGNAL(clicked()),this,SLOT(insertChild()));
     updateActions();
  }
 else
     QMessageBox::warning(this, tr("Внимание"), tr("Файл не найден!"));
}

bool Widget::load(QString name) {
    name.prepend(":/");
    Q_INIT_RESOURCE(simpletreemodel);
    QFile file(name);
    if (file.open(QIODevice::ReadOnly)) {
        //Создаем заголовки столбцов:
        QStringList headers;
        headers << tr("Заголовок") << tr("Описание");
        bool fl = ui->treeView->rootIndex().isValid(); // model();
        qDebug()<<fl;
        if (fl && deleteTree())
            return 1;

        Tree *tree = new Tree(headers, file.readAll());
        file.close();
        ui->treeView->setModel(tree);
        return 0;
    }
    else
        return 1;
}

void Widget::insertChild() {
 //Получаем индекс узла и модель элемента:
 QModelIndex index = ui->treeView->selectionModel()->currentIndex();
 QAbstractItemModel *model = ui->treeView->model();
 //Вставляем данные:
 if (model->columnCount(index) == 0)
    if (!model->insertColumn(0, index))
        return;
 if (!model->insertRow(0, index)) return;
 //Инициализируем их:
 for (int column = 0; column < model->columnCount(index); ++column) {
  QModelIndex child = model->index(0, column, index);
  model->setData(child, QVariant("Данные"), Qt::EditRole);
  if (!model->headerData(column, Qt::Horizontal).isValid())
   model->setHeaderData(column, Qt::Horizontal, QVariant("Столбец"), Qt::EditRole);
  }
 //Выбираем вставленный узел:
  ui->treeView->selectionModel()->setCurrentIndex(model->index(0, 0, index),
  QItemSelectionModel::ClearAndSelect);

  updateActions();
}

void Widget::insertRow() {
 QModelIndex index = ui->treeView->selectionModel()->currentIndex();
 QAbstractItemModel *model = ui->treeView->model();
 if (!model->insertRow(index.row()+1, index.parent())) return;
 updateActions();
 for (int column = 0; column < model->columnCount(index.parent()); ++column) {
  QModelIndex child = model->index(index.row()+1, column, index.parent());
  model->setData(child, QVariant("Данные"), Qt::EditRole);
 }
}

void Widget::removeRow() {
 QModelIndex index = ui->treeView->selectionModel()->currentIndex();
 QAbstractItemModel *model = ui->treeView->model();
 if (model->removeRow(index.row(), index.parent())) updateActions();
}

bool Widget::deleteTree() {
 QAbstractItemModel *model = ui->treeView->model();
 if(model->removeRows(0,model->rowCount())){
     return 0;
 }
 else
     return 1;
}

void Widget::updateActionButtons() {
 updateActions();
}

void Widget::updateActions() {
 /*bool hasSelection = !ui->treeView->selectionModel()->selection().isEmpty();
 ui->removeRowAction->setEnabled(hasSelection);
 ui->insertRowAction->setEnabled(hasSelection);
 ui->insertChildAction->setEnabled(hasSelection);
 bool hasCurrent = ui->treeView->selectionModel()->selection();
 ui->removeRowAction->setEnabled(hasCurrent);
 ui->insertRowAction->setEnabled(hasCurrent);
 ui->insertChildAction->setEnabled(hasCurrent);*/
}

void Widget::on_load_clicked()
{
    ui->label->show();
    ui->lineEdit->show();
    ui->Ok->show();
    ui->Cancel->show();
    ui->load->hide();
    ui->save->hide();
}

void Widget::on_save_clicked()
{
    if(!save()) {
        QMessageBox::information(this, tr("Сохранено"), tr("Данные сохранены в файл!"));
    }
    else
        QMessageBox::warning(this, tr("Внимание"), tr("Файл не найден!"));

}

void Widget::on_Ok_clicked()
{
    if (!load(ui->lineEdit->text())) {
        ui->label->hide();
        ui->lineEdit->hide();
        ui->Ok->hide();
        ui->Cancel->hide();
        ui->load->show();
        ui->save->show();
    }
    else
        QMessageBox::warning(this, tr("Внимание"), tr("Файл не найден!"));
}

void Widget::on_Cancel_clicked()
{
    ui->label->hide();
    ui->lineEdit->hide();
    ui->Ok->hide();
    ui->Cancel->hide();
    ui->load->show();
    ui->save->show();
}

bool Widget::save() {
    QFile file("/home/jinxx/Dropbox/VP_LABS/5_lab_good/5.1/result.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    // Создаем объект класса QTextStream и передаем ему адрес объекта file
    QModelIndex index=ui->treeView->model()->index(0,0);//rootIndex();// = ui->treeView->selectionModel()->currentIndex();
    QStringList model;

    //QAbstractItemModel *model = ui->treeView->model();
    while(1) {
        index=rec(index,file);
        if(index.child(0,0).isValid())
            continue;
        else
            break;
    }
    //if(model->hasChildren())
      //  rec(index.child(1,0),file);
    QObjectList list=ui->treeView->selectionModel()->children();// selectionModel()->currentIndex();
    //ui->treeView->setModel(model);
    qDebug()<<list.count();


    //ui->treeView->setTreePosition(index);

    index = ui->treeView->selectionModel()->currentIndex();
    rec(index,file);

    //QObjectList children=ui->treeView->children();
    //QVector <QVariant> columnData;
    //columnData<<children.at(1);

    //index.child()
    //QString str=index.row().toString();
    //qDebug<<columnData.at(0);
    //rec(index.child(0,1),file);

    file.close();
        return 0;
    }
    else
        return 1;
}

QModelIndex Widget::rec(const QModelIndex& index, QFile& file) {
    QAbstractItemModel *model = ui->treeView->model();
    QModelIndex child;
    QTextStream writeStream(&file);
    int size = model->rowCount(index);
    for(int i=0; i<size; i++) {
        for (int column = 0; column < model->columnCount(index); ++column) {
           child = model->index(i, column,index);
           QVariant item=model->data(child);
           QString str=item.toString();
           if(column)
               str.prepend(":::");
           writeStream << str;
           qDebug()<<index<<index.row()-1<<str<<column;
         }
        writeStream << "\n";
        child=child.sibling(i,0);
    }
    return index;

    //QObjectList children=model->children();
    //s
    //qDebug<<children;
}
