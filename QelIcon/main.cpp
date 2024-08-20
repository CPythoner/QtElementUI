#include "QelIconTester.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QelIconTester tester;
    tester.setWindowTitle("Icon Tester");
    tester.show();

    return app.exec();
}

