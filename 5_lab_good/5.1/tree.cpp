#include "item.h"
#include "tree.h"
#include <QDebug>

Tree::Tree(const QStringList &headers, const QString &data, QObject *parent)
    : QAbstractItemModel(parent) {

 QVector <QVariant> rootData;
 rootData << "Узел" << "Описание"; //В модели будет 2 столбца
 rootItem = new Item(rootData);
  //Создали корневой элемент
 setupModelData(data.split(QString("\n")), rootItem);
  //Данные о строках модели разделены переводом строки
}

Tree::~Tree() { delete rootItem; }

int Tree::columnCount(const QModelIndex &parent) const {
 return rootItem->columnCount();
}

QVariant Tree::data (const QModelIndex &index, int role) const {
 if (!index.isValid()) return QVariant();
 if (role != Qt::DisplayRole  && role != Qt::EditRole) return QVariant();
 Item *item = getItem(index);
 return item->data(index.column());
}

Item *Tree::getItem(const QModelIndex &index) const {
 if (index.isValid()) {
  Item *item = static_cast<Item*>(index.internalPointer());
  if (item) return item;
 }
 return rootItem;
}

Qt::ItemFlags Tree::flags(const QModelIndex &index) const {
 if (!index.isValid()) return 0;
 return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant Tree::headerData(int section, Qt::Orientation orientation, int role) const {
 if (orientation == Qt::Horizontal && role == Qt::DisplayRole) return rootItem->data(section);
 return QVariant();
}

QModelIndex Tree::index(int row, int column, const QModelIndex &parent) const {
 if (parent.isValid() && parent.column() != 0) return QModelIndex();
 Item *parentItem = getItem(parent);
 Item *childItem = parentItem->child(row);
 if (childItem) return createIndex(row, column, childItem);
 else return QModelIndex();
}

QModelIndex Tree::parent(const QModelIndex &index) const {
 if (!index.isValid()) return QModelIndex();
 Item *childItem = getItem(index);
 Item *parentItem = childItem->parentItem();
 if (parentItem == rootItem) return QModelIndex();
 return createIndex(parentItem->childNumber(), 0, parentItem);
}

int Tree::rowCount(const QModelIndex &parent) const {
 Item *parentItem = getItem(parent);
 return parentItem->childCount();
}

void Tree::setupModelData(const QStringList &lines, Item *parent) {
 QList<Item*> parents;
 QList<int> indentations;
 parents << parent;
 indentations << 0;
 int number = 0;
 //Ищем первый непробельный символ с номером position
 while (number < lines.count()) {
  int position = 0;
  while (position < lines[number].length()) {
  if (lines[number].at(position) != ' ') break;
  position++;
 }
 //Отрезаем пробельное начало строки
 QString lineData = lines[number].mid(position).trimmed();
 if (!lineData.isEmpty()) {
  //Читаем остальную часть строки, если она есть
  QStringList columnStrings = lineData.split(":::", QString::SkipEmptyParts);
   //Учитываем разделитель столбцов
  QVector <QVariant> columnData; //Список данных столбцов
  for (int column = 0; column < columnStrings.count(); ++column)
   columnData << columnStrings[column];
  if (position > indentations.last()) {
   //Последний потомок текущего родителя теперь будет новым родителем,
   //пока у текущего родителя нет потомков
   if (parents.last()->childCount() > 0) {
    parents << parents.last()->child(parents.last()->childCount()-1);
    indentations << position;
   }
  }
  else {
   while (position < indentations.last() && parents.count() > 0) {
    parents.pop_back();
    indentations.pop_back();
   }
  }
  //Добавить новый узел в список потомков текущего родителя
  parents.last()->appendChild(new Item(columnData, parents.last()));
 }
 ++number;
 }
}

bool Tree::setData(const QModelIndex &index, const QVariant &value, int role) {
 if (role != Qt::EditRole) return false;
 Item *item = getItem(index);
 bool result = item->setData(index.column(), value);
 if (result) {
  emit dataChanged(index, index);
 }
 return result;
}

bool Tree::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role) {
 if (role != Qt::EditRole || orientation != Qt::Horizontal) return false;
 bool result = rootItem->setData(section, value);
 if (result) {
  emit headerDataChanged(orientation, section, section);
 }
 return result;
}

bool Tree::insertRows(int position, int rows, const QModelIndex &parent) {
 Item *parentItem = getItem(parent);
 bool success;
 beginInsertRows(parent, position, position + rows - 1);
 success = parentItem->insertChildren(position, rows, rootItem->columnCount());
 endInsertRows();
 return success;
}

bool Tree::removeRows(int position, int rows, const QModelIndex &parent) {
 Item *parentItem = getItem(parent);

 bool success = true;
 beginRemoveRows(parent, position, position + rows - 1);
 success = parentItem->removeChildren(position, rows);
 endRemoveRows();
 return success;
}

