#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //создаем верхнее меню
    QMenuBar mnuBar;
    QMenu   *pmnu   = new QMenu("&Menu");
    pmnu->addAction("&About Qt",
                        &a,
                        SLOT(aboutQt()),
                        Qt::CTRL + Qt::Key_Q
                       );
    pmnu->addAction("Exit",
                    &a,
                    SLOT(quit()),
                    Qt::CTRL + Qt::Key_C);
    mnuBar.addMenu(pmnu);
    //pmnu->addSeparator();//добавили разделитель в выпадающее меню
    // создаем окно-родитель
    QWidget *window = new QWidget();
    window->setWindowTitle("Lab1");
    QPushButton *btn_quit1 = new QPushButton("Close");
    // создаем виджеты
    QSpinBox *spinBox = new QSpinBox();
    QSlider *sliderH = new QSlider(Qt::Horizontal);
    QSlider *sliderV = new QSlider(Qt::Vertical);
    // задаем минимальное и максимальное значение спина и слайдеров
    spinBox->setRange(0, 150);
    sliderH->setRange(0, 150);
    sliderV->setRange(0, 150);
    // связываем сигналы и слоты слайдеров и спина
    QObject::connect(spinBox,
                     SIGNAL(valueChanged(int)),
                     sliderH,
                     SLOT(setValue(int))
                     );
    QObject::connect(sliderH,
                     SIGNAL(valueChanged(int)),
                     spinBox,
                     SLOT((setValue(int)))
                     );
    QObject::connect(spinBox,
                     SIGNAL(valueChanged(int)),
                     sliderV,
                     SLOT(setValue(int))
                     );
    QObject::connect(sliderV,
                     SIGNAL(valueChanged(int)),
                     spinBox,
                     SLOT((setValue(int)))
                     );
    QObject::connect(btn_quit1,
                     SIGNAL(clicked()),
                     &a,
                     SLOT (quit())
                     );
    spinBox->setValue(30);
    //создадим поле компановки виджетов
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(&mnuBar);
    layout->addWidget(spinBox);
    layout->addWidget(sliderH);
    layout->addWidget(sliderV);
    layout->addWidget(btn_quit1);
    window->setLayout(layout);
    //mnuBar.show();
    window->show();
    return a.exec();
}
