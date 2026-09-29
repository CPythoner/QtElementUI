#include "QelBadgeTester.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QelBadgeTester tester;
    tester.resize(820, 680);
    tester.show();

    return application.exec();
}
