#include <QApplication>
#include "QelRadioTester.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QelRadioTester tester;
    tester.resize(420, 240);
    tester.show();

    return app.exec();
}
