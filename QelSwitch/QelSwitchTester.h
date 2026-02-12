#ifndef QELSWITCHTESTER_H
#define QELSWITCHTESTER_H

#include "QelSwitch.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

using qel::QelSwitch;

class QelSwitchTester : public QWidget {
public:
    explicit QelSwitchTester(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(14);

        QLabel *title = new QLabel("QelSwitch 示例", this);
        mainLayout->addWidget(title);

        QHBoxLayout *row1 = new QHBoxLayout();
        QelSwitch *on = new QelSwitch(this);
        on->setChecked(true);
        QLabel *onLabel = new QLabel("开启", this);
        row1->addWidget(on);
        row1->addWidget(onLabel);
        row1->addStretch();

        QHBoxLayout *row2 = new QHBoxLayout();
        QelSwitch *off = new QelSwitch(this);
        QLabel *offLabel = new QLabel("关闭", this);
        row2->addWidget(off);
        row2->addWidget(offLabel);
        row2->addStretch();

        QHBoxLayout *row3 = new QHBoxLayout();
        QelSwitch *disabled = new QelSwitch(this);
        disabled->setChecked(true);
        disabled->setDisabled(true);
        QLabel *disabledLabel = new QLabel("禁用", this);
        row3->addWidget(disabled);
        row3->addWidget(disabledLabel);
        row3->addStretch();

        QHBoxLayout *row4 = new QHBoxLayout();
        QelSwitch *small = new QelSwitch(this);
        small->setSize(QelSwitch::Size::Small);
        QLabel *smallLabel = new QLabel("小尺寸", this);
        row4->addWidget(small);
        row4->addWidget(smallLabel);
        row4->addStretch();

        mainLayout->addLayout(row1);
        mainLayout->addLayout(row2);
        mainLayout->addLayout(row3);
        mainLayout->addLayout(row4);
        mainLayout->addStretch();
    }
};

#endif // QELSWITCHTESTER_H
