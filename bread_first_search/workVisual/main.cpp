#include "workVisual.h"
#include <QtWidgets/QApplication>
#include <windows.h>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    workVisual w;
    w.show();
    w.makeDots();
    w.setImageLabel("output0.png");
    return a.exec();
}
