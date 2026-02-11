#include <QApplication>
#include "QelSwitchTester.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QelSwitchTester tester;
    tester.resize(420, 260);
    tester.show();

    return app.exec();
}
