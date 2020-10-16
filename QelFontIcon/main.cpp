#include "QelFontIcon.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QelFontIcon w;
    w.show();

    return a.exec();
}
