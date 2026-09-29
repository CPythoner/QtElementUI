#include "QelProgressTester.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QelProgressTester tester;
    tester.resize(900, 900);
    tester.show();

    return application.exec();
}
