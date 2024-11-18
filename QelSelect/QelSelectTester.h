#ifndef QELSELECTTESTER_H
#define QELSELECTTESTER_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include "QelSelect.h"

class QelSelectTester : public QMainWindow
{
    Q_OBJECT

public:
    explicit QelSelectTester(QWidget *parent = nullptr)
        : QMainWindow(parent)
    {
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

        // 基础用法
        QLabel *basicLabel = new QLabel("基础用法", this);
        basicSelect = new QelSelect(this);
        basicSelect->setPlaceholder("请选择");

        // 禁用状态
        QLabel *disabledLabel = new QLabel("禁用状态", this);
        disabledSelect = new QelSelect(this);
        disabledSelect->setDisabled(true);
        disabledSelect->setPlaceholder("禁用状态");

        // 可清空选项
        QLabel *clearableLabel = new QLabel("可清空选项", this);
        clearableSelect = new QelSelect(this);
        clearableSelect->setClearable(true);
        clearableSelect->setPlaceholder("可清空");

        // 可筛选选项
        QLabel *filterableLabel = new QLabel("可筛选选项", this);
        filterableSelect = new QelSelect(this);
        filterableSelect->setFilterable(true);
        filterableSelect->setPlaceholder("可筛选");

        // 添加到布局
        mainLayout->addWidget(basicLabel);
        mainLayout->addWidget(basicSelect);
        mainLayout->addSpacing(20);

        mainLayout->addWidget(disabledLabel);
        mainLayout->addWidget(disabledSelect);
        mainLayout->addSpacing(20);

        mainLayout->addWidget(clearableLabel);
        mainLayout->addWidget(clearableSelect);
        mainLayout->addSpacing(20);

        mainLayout->addWidget(filterableLabel);
        mainLayout->addWidget(filterableSelect);

        mainLayout->addStretch();

        // 设置窗口大小
        resize(800, 600);

        // 添加示例选项
        QStringList options = {"选项1", "选项2", "选项3", "选项4", "选项5"};
        basicSelect->addItems(options);
        disabledSelect->addItems(options);
        clearableSelect->addItems(options);
        filterableSelect->addItems(options);
    }

private:
    QelSelect *basicSelect;
    QelSelect *disabledSelect;
    QelSelect *clearableSelect;
    QelSelect *filterableSelect;
};

#endif // QELSELECTTESTER_H
