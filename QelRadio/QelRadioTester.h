#ifndef QELRADIOTESTER_H
#define QELRADIOTESTER_H

#include "QelRadio.h"

#include <QButtonGroup>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

using qel::QelRadio;

class QelRadioTester : public QWidget {
public:
    explicit QelRadioTester(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(12);

        QLabel *title = new QLabel("QelRadio 示例", this);
        mainLayout->addWidget(title);

        QButtonGroup *group = new QButtonGroup(this);
        QelRadio *a = new QelRadio("选项 A", this);
        QelRadio *b = new QelRadio("选项 B", this);
        QelRadio *c = new QelRadio("禁用选项", this);
        c->setDisabled(true);

        a->setChecked(true);
        group->addButton(a);
        group->addButton(b);
        group->addButton(c);

        QelRadio *small = new QelRadio("小尺寸", this);
        small->setSize(QelRadio::Size::Small);

        mainLayout->addWidget(a);
        mainLayout->addWidget(b);
        mainLayout->addWidget(c);
        mainLayout->addWidget(small);
        mainLayout->addStretch();
    }
};

#endif // QELRADIOTESTER_H
