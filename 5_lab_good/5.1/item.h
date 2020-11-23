#ifndef Item_H
#define Item_H
#include <QList>
#include <QVector>
#include <QVariant>
class Item { //Класс узла дерева
public:
 explicit Item (const QVector<QVariant> &data,
 Item *parentItem = 0);
 ~Item();

 void appendChild(Item *child); //Добавить узел-потомок
 Item *child(int row); //Вернуть дочерний элемент
 int childCount() const; //Количество дочерних элементов
 int columnCount() const; //Вернуть количество столбцов элемента
 QVariant data(int column) const; //Вернуть данные указанного столбца
 int childNumber() const; //Вернуть номер строки элемента

 Item *parentItem(); //Вернуть родительский элемент
 bool insertChildren(int position, int count, int columns); //Вставить потомков (строки)
 bool removeChildren(int position, int count);  //Удалить потомков
 bool setData(int column, const QVariant &value); //Установить данные
private: //Внутреннее представление данных:
 QList <Item*> m_childItems; //Список дочерних элементов
 QVector <QVariant> m_itemData; //Список данных текущего узла
 Item *m_parentItem; //Ссылка на родительский узел
};
#endif // Item_H
