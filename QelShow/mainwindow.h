#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "../QelIcon/QelIconTester.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStackedWidget *p_stacked_widget_;
    QelIconTester  *p_qelicon_tester_ = nullptr;
};

#endif // MAINWINDOW_H
