#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pStackedWidget(new QStackedWidget(this))
{
    // 创建左侧的树状列表
    QTreeWidget *treeWidget = new QTreeWidget(this);
    treeWidget->setHeaderLabel("QtElementUI Show");

    // 创建组件测试页面
    pQelIconTester = new QelIconTester(this);
    pQelButtonTester = new QelButtonTester(this);
    pQelNumberInputTester = new QelNumberInputTester(this);

    // 创建页面与树项映射关系
    pageMap["QelIcon"] = pQelIconTester;
    pageMap["QelButton"] = pQelButtonTester;
    pageMap["QelNumberInput"] = pQelNumberInputTester;

    // 添加树状列表的项目
    addTreeItem(treeWidget, "QelIcon");
    addTreeItem(treeWidget, "QelButton");
    addTreeItem(treeWidget, "QelNumberInput");

    // 将所有页面添加到 QStackedWidget
    for (QWidget *page : pageMap.values()) {
        pStackedWidget->addWidget(page);
    }

    // 创建一个主容器 QWidget，设置为 central widget
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // 设置布局
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addWidget(treeWidget, 1); // 左侧树状列表占1份
    mainLayout->addWidget(pStackedWidget, 3); // 右侧页面展示占3份

    // 连接树状列表的点击信号和页面切换槽函数
    connect(treeWidget, &QTreeWidget::itemClicked, [=](QTreeWidgetItem *item, int) {
        if (pageMap.contains(item->text(0))) {
            pStackedWidget->setCurrentWidget(pageMap[item->text(0)]);
        } else {
            // 当选择了不存在的树项时显示默认页面
            pStackedWidget->setCurrentWidget(new QLabel("No Page Found", this));
        }
    });

            // 设置主窗口的尺寸策略
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTreeItem(QTreeWidget *treeWidget, const QString &name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget);
    item->setText(0, name);
}
