#include <QApplication>
#include <QMainWindow>
#include "QelButtonTester.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    QelButtonTester *tester = new QelButtonTester();
    mainWindow.setCentralWidget(tester);
    mainWindow.resize(800, 600);
    mainWindow.show();

    return app.exec();
}
