#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTreeWidget>

#include "../QelIcon/QelIconTester.h"
#include "../QelButton/QelButtonTester.h"
#include "../QelNumberInput/QelNumberInputTester.h"
#include "../QelInput/QelInputTester.h"
#include "../QelSelect/QelSelectTester.h"
#include "../QelCheckbox/QelCheckboxTester.h"
#include "../QelRadio/QelRadioTester.h"
#include "../QelSwitch/QelSwitchTester.h"

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
    QTreeWidgetItem *addTreeItem(QTreeWidget *treeWidget, const QString &name);
    QTreeWidgetItem *addTreeItem(QTreeWidgetItem *parent, const QString &name);

private:
    Ui::MainWindow *ui;
    QMap<QString, QWidget*> pageMap;
    QStackedWidget *pStackedWidget;
    QelIconTester  *pQelIconTester = nullptr;
    QelButtonTester *pQelButtonTester = nullptr;
    QelNumberInputTester *pQelNumberInputTester = nullptr;
    QelInputTester *pQelInputTester = nullptr;
    QelSelectTester *pQelSelectTester = nullptr;
    QelCheckboxTester *pQelCheckboxTester = nullptr;
    QelRadioTester *pQelRadioTester = nullptr;
    QelSwitchTester *pQelSwitchTester = nullptr;
};

#endif // MAINWINDOW_H

