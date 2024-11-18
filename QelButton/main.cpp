#include <QApplication>
#include <QMainWindow>
#include "QelButtonTester.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 创建主窗口
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("QelButton Demo");

    // 创建测试器实例
    QelButtonTester *tester = new QelButtonTester(&mainWindow);
    mainWindow.setCentralWidget(tester);

    // 设置合适的窗口大小
    mainWindow.resize(800, 600);
    mainWindow.show();

    return app.exec();
}
