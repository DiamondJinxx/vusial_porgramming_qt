#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    count = 0;
    ui->treeWidget->setColumnCount(1);
    QStringList headers;
    headers << tr("Объекты");
    ui->treeWidget->setHeaderLabels(headers);
    currentItem = NULL;
    currentColumn = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{

}

void MainWindow::on_btn_add_clicked()
{

}

void MainWindow::on_btn_del_clicked()
{

}

int MainWindow::treeCount(QTreeWidget *tree, QTreeWidgetItem *parent)
{
    tree->expandAll();
    int count = 0;
    if (parent == 0)
    {
        int topCount = tree->topLevelItemCount();
        for(int i = 0; i < topCount; i++)
        {
            QTreeWidgetItem *item = tree->topLevelItem(i);
            if (item->isExpanded())
                count += treeCount(tree, item);
        }
        count += topCount;
    }
    else
    {
        int childCount = parent->childCount();
        for (int i = 0; i < childCount; ++i) {
            QTreeWidgetItem *item = parent->child(i);
            if(item->isExpanded()) count += treeCount(tree, item);
        }
        count += childCount;
    }
    return count;
}

void MainWindow::deleteItem(QTreeWidgetItem *currentItem)
{
    QTreeWidgetItem *parent = currentItem->parent();
    int index;
    if(parent)
    {
        index = parent->indexOfChild(ui->treeWidget->currentItem());
        delete parent->takeChild(index);
    }
    else
    {
        index = ui->treeWidget->indexOfTopLevelItem(ui->treeWidget->currentItem());
        delete ui->treeWidget->takeTopLevelItem(index);
    }
}
