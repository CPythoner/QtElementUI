#include <QApplication>

#include "QelFormTester.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QelFormTester tester;
    tester.resize(720, 520);
    tester.show();

    return app.exec();
}
