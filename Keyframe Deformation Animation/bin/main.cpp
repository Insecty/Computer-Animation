#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("Vector-Linear-Interpolation Demo");
    w.show();

    return a.exec();
}
