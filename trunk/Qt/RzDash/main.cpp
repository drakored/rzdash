#include <QtGui/QApplication>
#include "rzdash.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rzdash w;
    w.show();

    return a.exec();
}
