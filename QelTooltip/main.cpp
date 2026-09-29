#include "QelTooltipTester.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QelTooltipTester tester;
    tester.resize(760, 620);
    tester.show();

    return application.exec();
}
