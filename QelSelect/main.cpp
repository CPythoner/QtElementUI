#include <QApplication>
#include "QelSelectTester.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QelSelectTester w;
    w.show();
    return a.exec();
}
