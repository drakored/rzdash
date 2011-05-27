#include <QtGui/QApplication>
#include "dmul.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dmul w;
    w.show();

    return a.exec();
}
