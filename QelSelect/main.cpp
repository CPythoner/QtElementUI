#include <QApplication>

#include "QelSelectTester.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QelSelectTester tester;
    tester.show();
    return app.exec();
}
