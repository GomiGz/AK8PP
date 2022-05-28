#include "backprocess.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BackProcess w;
    w.show();
    return a.exec();
}
