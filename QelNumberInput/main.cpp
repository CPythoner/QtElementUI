#include <QApplication>
#include <QMainWindow>
#include "QelNumberInputTester.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    QelNumberInputTester *tester = new QelNumberInputTester();
    mainWindow.setCentralWidget(tester);
    mainWindow.resize(800, 600);
    mainWindow.show();

    return app.exec();
}
