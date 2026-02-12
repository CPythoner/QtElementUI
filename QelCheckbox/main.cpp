#include <QApplication>
#include "QelCheckboxTester.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QelCheckboxTester tester;
    tester.resize(420, 260);
    tester.show();

    return app.exec();
}
