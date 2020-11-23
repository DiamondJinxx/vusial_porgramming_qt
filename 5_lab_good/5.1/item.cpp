#include "item.h"
Item::Item (const QVector<QVariant> &data, Item *parent) {
 //Конструктору узла нужно передать данные и ссылку на родителя
 m_parentItem = parent;
 m_itemData = data;
}
Item::~Item() { qDeleteAll(m_childItems); }
/* Методы класса служат, по сути, интерфейсом к
 соответствующим методам стандартного класса QVector: */

void Item::appendChild(Item *item) {
 m_childItems.append(item);
 //Добавить узел в список потомков
}

Item *Item::child (int row) {
 return m_childItems.value(row);
 //По номеру строки выбрать нужного потомка из списка
}

int Item::childCount() const {
 return m_childItems.count();
 //Количество потомков узла = длине списка потомков
}

int Item::columnCount() const {
 return m_itemData.count();
 //Количество столбцов в узле = длине списка данных узла
}

QVariant Item::data (int column) const {
 return m_itemData.value(column);
 //Взять данные из нужного столбца
}

Item *Item::parentItem() {
 return m_parentItem; //Вернуть ссылку на родителя
}

int Item::childNumber() const {
 //Если есть родитель - найти свой номер в списке его потомков
 if (m_parentItem) return m_parentItem->m_childItems.indexOf(const_cast<Item*>(this));
 return 0; //Иначе вернуть 0
}

bool Item::insertChildren(int position, int count, int columns) {
 if (position < 0 || position > m_childItems.size()) return false;
 for (int row = 0; row < count; ++row) {
  QVector<QVariant> data(columns);
  Item *item = new Item(data, this);
  m_childItems.insert(position, item);
 }
 return true;
}

bool Item::removeChildren(int position, int count) {
 if (position < 0 || position + count > m_childItems.size()) return false;
 for (int row = 0; row < count; ++row) delete m_childItems.takeAt(position);
 return true;
}

// Ставит значение value в столбец column элемента:
bool Item::setData(int column, const QVariant &value) {
 if (column < 0 || column >= m_itemData.size()) return false;
 m_itemData[column] = value;
 return true;
}
