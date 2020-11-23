#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    QSpinBox *sb = new QSpinBox();
    QSlider *sd  = new QSlider(Qt::Vertical);
    QWidget *window = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout();

    sb->setMaximum(100);
    sd->setMaximum(100);

    layout->addWidget(sd);
    layout->addWidget(sb);

    window->resize(300,300);
    window->setLayout(layout);
    QObject::connect(sb,SIGNAL(valueChanged(int)),sd,SLOT(setValue(int)));
    QObject::connect(sd,SIGNAL(valueChanged(int)),sb,SLOT(setValue(int)));
    window->show();

    return app.exec();
}
