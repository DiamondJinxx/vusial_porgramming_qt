/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *insertRowAction;
    QPushButton *removeRowAction;
    QPushButton *insertChildAction;
    QTreeView *treeView;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *Ok;
    QPushButton *Cancel;
    QPushButton *load;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *save;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(519, 534);
        horizontalLayout_2 = new QHBoxLayout(Widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        insertRowAction = new QPushButton(Widget);
        insertRowAction->setObjectName(QString::fromUtf8("insertRowAction"));

        horizontalLayout->addWidget(insertRowAction);

        removeRowAction = new QPushButton(Widget);
        removeRowAction->setObjectName(QString::fromUtf8("removeRowAction"));

        horizontalLayout->addWidget(removeRowAction);

        insertChildAction = new QPushButton(Widget);
        insertChildAction->setObjectName(QString::fromUtf8("insertChildAction"));

        horizontalLayout->addWidget(insertChildAction);


        verticalLayout->addLayout(horizontalLayout);

        treeView = new QTreeView(Widget);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout->addWidget(treeView);

        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        Ok = new QPushButton(Widget);
        Ok->setObjectName(QString::fromUtf8("Ok"));

        verticalLayout->addWidget(Ok);

        Cancel = new QPushButton(Widget);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));

        verticalLayout->addWidget(Cancel);

        load = new QPushButton(Widget);
        load->setObjectName(QString::fromUtf8("load"));

        verticalLayout->addWidget(load);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));

        verticalLayout->addLayout(horizontalLayout_3);

        save = new QPushButton(Widget);
        save->setObjectName(QString::fromUtf8("save"));

        verticalLayout->addWidget(save);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        insertRowAction->setText(QCoreApplication::translate("Widget", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\203\320\267\320\265\320\273 \321\202\320\276\320\263\320\276 \320\266\320\265 \321\203\321\200\320\276\320\262\320\275\321\217", nullptr));
        removeRowAction->setText(QCoreApplication::translate("Widget", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\275\321\213\320\271 \321\203\320\267\320\265\320\273", nullptr));
        insertChildAction->setText(QCoreApplication::translate("Widget", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\277\320\276\321\202\320\276\320\274\320\272\320\260", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\204\320\260\320\271\320\273\320\260 (\321\201 \321\200\320\260\321\201\321\210\320\270\321\200\320\265\320\275\320\270\320\265\320\274)", nullptr));
        Ok->setText(QCoreApplication::translate("Widget", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
        Cancel->setText(QCoreApplication::translate("Widget", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        load->setText(QCoreApplication::translate("Widget", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\264\320\265\321\200\320\265\320\262\320\276 \320\270\320\267 \321\204\320\260\320\271\320\273\320\260", nullptr));
        save->setText(QCoreApplication::translate("Widget", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\264\320\265\321\200\320\265\320\262\320\276 \320\262 \321\204\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
