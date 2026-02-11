#ifndef QELSELECTTESTER_H
#define QELSELECTTESTER_H

#include "QelSelect.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

using qel::QelSelect;

class QelSelectTester : public QWidget {
public:
    explicit QelSelectTester(QWidget *parent = nullptr) : QWidget(parent)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(16);

        mainLayout->addWidget(createCase("基础用法", []() {
            QelSelect *select = new QelSelect();
            select->addOption("北京", "beijing");
            select->addOption("上海", "shanghai");
            select->addOption("广州", "guangzhou");
            select->setCurrentValue("shanghai");
            return select;
        }));

        mainLayout->addWidget(createCase("禁用状态", []() {
            QelSelect *select = new QelSelect();
            select->setOptions({"选项 A", "选项 B", "选项 C"});
            select->setDisabled(true);
            return select;
        }));

        mainLayout->addWidget(createCase("不同尺寸", []() {
            QWidget *container = new QWidget();
            QVBoxLayout *layout = new QVBoxLayout(container);

            QelSelect *large = new QelSelect();
            large->setSize(QelSelect::Size::Large);
            large->setOptions({"Large 选项"});

            QelSelect *normal = new QelSelect();
            normal->setSize(QelSelect::Size::Default);
            normal->setOptions({"Default 选项"});

            QelSelect *small = new QelSelect();
            small->setSize(QelSelect::Size::Small);
            small->setOptions({"Small 选项"});

            layout->addWidget(large);
            layout->addWidget(normal);
            layout->addWidget(small);
            return container;
        }));

        setLayout(mainLayout);
    }

private:
    template<typename Factory>
    QWidget* createCase(const QString &title, Factory factory)
    {
        QWidget *container = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(container);

        QLabel *label = new QLabel(title, container);
        layout->addWidget(label);
        layout->addWidget(factory());

        return container;
    }
};

#endif // QELSELECTTESTER_H
