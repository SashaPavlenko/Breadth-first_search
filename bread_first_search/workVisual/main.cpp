#include "workVisual.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    workVisual w;
    w.show();
    w.makeDot();
    
    return a.exec();
}
