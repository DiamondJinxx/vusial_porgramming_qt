#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :  QWidget(parent), ui(new Ui::Widget)
{

    ui->setupUi(this);
    //ниже наша часть конструктора
    QPixmap bckgnd(":/img/tak.jpg");
    bckgnd = bckgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    palette.setBrush(QPalette::Background,bckgnd);
    this->setPalette(palette);
    count = 0;
    ui->treeWidget->setColumnCount(1);
    QStringList headers;
    headers << tr("Иерархия птиц");
    ui->treeWidget->setHeaderLabels(headers);
    currentItem = NULL;
    currentColumn = 0;
    QFile file("tree.txt");
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        treeRead(&file, ui->treeWidget);
        //file.write("Test string\n");
        //file.write("Test string2");
        file.close();
    }
}

Widget::~Widget() { delete ui; }

int Widget::treeCreate(QFile *file, QTreeWidget *tree, QTreeWidgetItem *parent = 0)
{
    /*
     не учтёт свёрнутые ветви; потому что правильно было бы делать через модель
    */
    tree->expandAll(); //а это "костыль"
    int count = 0;
    if (parent == 0)
    {
        int topCount = tree->topLevelItemCount();
        for (int i = 0; i < topCount; i++)
        {
            QTreeWidgetItem *item = tree->topLevelItem(i);
            if (item->isExpanded())
            {
                QString str = item->text(currentColumn);
                file->write(str.toUtf8());
                count += treeCreate(file, tree, item);
                file->write("\n");
            }
        }
    count += topCount;
    }
    else
    {
        int childCount = parent->childCount();
        for (int i = 0; i < childCount; i++)
        {
            QTreeWidgetItem *item = parent->child(i);
            if (item->isExpanded())
            {
                file->write("\n<\n");
                QString str = item->text(currentColumn);
                file->write(str.toUtf8());
                count += treeCreate(file, tree, item);
                file->write("\n>");
            }
        }
        count += childCount;
    }
    //file->write(">\n");
    return count;

}


void Widget::DeleteItem (QTreeWidgetItem *currentItem)
{
    QTreeWidgetItem *parent = currentItem->parent();
    int index;
    if (parent)
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

void Widget::InsertItem (QTreeWidgetItem *parent, QString text)
{
    if (parent->isExpanded()==false) parent->setExpanded(true);
    QTreeWidgetItem *newItem = new QTreeWidgetItem(parent, ui->treeWidget->currentItem());
    newItem->setText (currentColumn, text);
    newItem->setExpanded(true);
}


void Widget::on_pushButton_clicked() //кнопка Добавить
{

    bool ok;
    QString str = QInputDialog::getText( 0, "Введите название птычки", "Название птычки:", QLineEdit::Normal, "Птычку?", &ok);
    if(ok)
    {
        if (currentItem)
        {
            QString word = currentItem->text(currentColumn);
            InsertItem  (currentItem, str);
        }
        else
        {
            QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->treeWidget, ui->treeWidget->currentItem());
            //указываем 2-м параметром текущий элемент как предшествующий
            newItem->setText (currentColumn, str);
            newItem->setExpanded(true);
        }
        currentItem = NULL;

    }
}

void Widget::on_pushButton_2_clicked() //кнопка Удалить
{
    if (currentItem)
    {
        DeleteItem (currentItem);
        currentItem = NULL;
    }
    //treeCount (ui->treeWidget);
}

void Widget::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    currentItem = item;
    currentColumn = column;
}

void Widget::on_pushButton_3_clicked()
{

    QFile file("tree.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        treeCreate(&file, ui->treeWidget);
        //file.write("Test string\n");
        //file.write("Test string2");
        file.close();
    }

}


int Widget::treeRead(QFile *file, QTreeWidget *)
{
    QString str="";
    int i=0;
    while(!file->atEnd())
    {
        str=file->readLine();
        if(!QString::compare(str,"<\n"))
        {
             str=file->readLine();
             //QMessageBox::information( this, "Не-не-не", str);
             //QString word = currentItem->text(currentColumn);
             InsertItem(currentItem, str);
             str=file->readLine();
             if(!QString::compare(str,"<\n"))
             {
                  str=file->readLine();
                  //QString word = currentItem->text(currentColumn);
                  InsertItem  (currentItem, str);
             }
        }
        else if(!QString::compare(str,">\n")) currentItem = NULL;
        else
        {
             QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->treeWidget, ui->treeWidget->currentItem());
             //указываем 2-м параметром текущий элемент как предшествующий
             newItem->setText (currentColumn, str);
             newItem->setExpanded(true);
             currentItem = newItem;
        }

    }
}

void Widget::on_pushButton_4_clicked()
{
    bool ok;
    QString str = QInputDialog::getText( 0, "Внесите изменения", "Название:", QLineEdit::Normal, currentItem->text(currentColumn), &ok);
    if(ok)
        currentItem->setText(currentColumn, str);
}
