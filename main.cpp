#include <QApplication>
#include "qvna.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qvna w;
    w.show();
    return a.exec();
}
