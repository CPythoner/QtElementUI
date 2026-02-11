#ifndef QELCHECKBOXTESTER_H
#define QELCHECKBOXTESTER_H

#include "QelCheckbox.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

using qel::QelCheckbox;

class QelCheckboxTester : public QWidget {
public:
    explicit QelCheckboxTester(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(12);

        QLabel *title = new QLabel("QelCheckbox 示例", this);
        mainLayout->addWidget(title);

        QelCheckbox *basic = new QelCheckbox("选项 A", this);
        basic->setChecked(true);

        QelCheckbox *indeterminate = new QelCheckbox("半选状态", this);
        indeterminate->setIndeterminate(true);

        QelCheckbox *disabled = new QelCheckbox("禁用状态", this);
        disabled->setChecked(true);
        disabled->setDisabled(true);

        QelCheckbox *small = new QelCheckbox("小尺寸", this);
        small->setSize(QelCheckbox::Size::Small);

        mainLayout->addWidget(basic);
        mainLayout->addWidget(indeterminate);
        mainLayout->addWidget(disabled);
        mainLayout->addWidget(small);
        mainLayout->addStretch();
    }
};

#endif // QELCHECKBOXTESTER_H
