#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTreeWidget>

#include "../QelIcon/QelIconTester.h"
#include "../QelButton/QelButtonTester.h"

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
    void addTreeItem(QTreeWidget *treeWidget, const QString &name);

private:
    Ui::MainWindow *ui;
    QMap<QString, QWidget*> pageMap;
    QStackedWidget *pStackedWidget;
    QelIconTester  *pQelIconTester = nullptr;
    QelButtonTester *pQelButtonTester = nullptr;
};

#endif // MAINWINDOW_H

