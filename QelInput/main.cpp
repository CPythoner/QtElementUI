#include <QApplication>

#include "QelInputTester.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QelInputTester tester;
    tester.show();
    return app.exec();
}
