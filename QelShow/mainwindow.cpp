#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    p_stacked_widget_(new QStackedWidget(this))
//    p_button_page_(new ButtonPage(this))
{
    // 创建左侧的树状列表
    QTreeWidget *treeWidget = new QTreeWidget(this);
    treeWidget->setHeaderLabel("QtElementUI Show");

    // 添加树状列表的项目
    QTreeWidgetItem *iconItem = new QTreeWidgetItem(treeWidget);
    iconItem->setText(0, "QelIcon");

    // 创建 QelIconTester 页面并添加到 QStackedWidget
    p_qelicon_tester_ = new QelIconTester(this);
    p_stacked_widget_->addWidget(p_qelicon_tester_);
    p_stacked_widget_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 创建一个主容器 QWidget，设置为 central widget
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // 设置布局
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addWidget(treeWidget, 1); // 左侧树状列表占1份
    mainLayout->addWidget(p_stacked_widget_, 3); // 右侧页面展示占3份

    // 连接树状列表的点击信号和页面切换槽函数
    connect(treeWidget, &QTreeWidget::itemClicked, [=](QTreeWidgetItem *item, int) {
        if (item->text(0) == "QelIcon") {
            p_stacked_widget_->setCurrentWidget(p_qelicon_tester_);
        }
    });

    // 设置主窗口的尺寸策略
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

MainWindow::~MainWindow()
{
    delete ui;
}
