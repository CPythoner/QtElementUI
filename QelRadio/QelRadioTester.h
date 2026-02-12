#ifndef QELRADIOTESTER_H
#define QELRADIOTESTER_H

#include "QelRadio.h"

#include <QButtonGroup>
#include <QHBoxLayout>
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
        mainLayout->setSpacing(16);

        mainLayout->addWidget(createTitle("基础用法"));
        {
            QHBoxLayout *row = new QHBoxLayout();
            row->setSpacing(16);

            QButtonGroup *group = new QButtonGroup(this);
            QelRadio *a = new QelRadio("Option 1", true, false, false, QelRadio::Size::Default, QelRadio::StyleType::Default, this);
            QelRadio *b = new QelRadio("Option 2", false, false, false, QelRadio::Size::Default, QelRadio::StyleType::Default, this);
            group->addButton(a);
            group->addButton(b);

            row->addWidget(a);
            row->addWidget(b);
            row->addStretch();
            mainLayout->addLayout(row);
        }

        mainLayout->addWidget(createTitle("禁用状态"));
        {
            QHBoxLayout *row = new QHBoxLayout();
            row->setSpacing(16);

            QButtonGroup *group = new QButtonGroup(this);
            QelRadio *uncheckedDisabled = new QelRadio("Disabled", false, true, false, QelRadio::Size::Default, QelRadio::StyleType::Default, this);
            QelRadio *checkedDisabled = new QelRadio("Disabled checked", true, true, false, QelRadio::Size::Default, QelRadio::StyleType::Default, this);
            group->addButton(uncheckedDisabled);
            group->addButton(checkedDisabled);

            row->addWidget(uncheckedDisabled);
            row->addWidget(checkedDisabled);
            row->addStretch();
            mainLayout->addLayout(row);
        }

        mainLayout->addWidget(createTitle("With borders"));
        {
            QHBoxLayout *row = new QHBoxLayout();
            row->setSpacing(16);

            QButtonGroup *group = new QButtonGroup(this);
            QelRadio *a = new QelRadio("Option 1", true, false, true, QelRadio::Size::Default, QelRadio::StyleType::Default, this);
            QelRadio *b = new QelRadio("Option 2", false, false, true, QelRadio::Size::Default, QelRadio::StyleType::Default, this);
            group->addButton(a);
            group->addButton(b);

            row->addWidget(a);
            row->addWidget(b);
            row->addStretch();
            mainLayout->addLayout(row);
        }

        mainLayout->addWidget(createTitle("Radio buttons"));
        {
            QHBoxLayout *row = new QHBoxLayout();
            row->setSpacing(0);

            QButtonGroup *group = new QButtonGroup(this);
            QelRadio *a = new QelRadio("Shanghai", true, false, false, QelRadio::Size::Default, QelRadio::StyleType::Button, this);
            QelRadio *b = new QelRadio("Beijing", false, false, false, QelRadio::Size::Default, QelRadio::StyleType::Button, this);
            QelRadio *c = new QelRadio("Guangzhou", false, false, false, QelRadio::Size::Default, QelRadio::StyleType::Button, this);
            group->addButton(a);
            group->addButton(b);
            group->addButton(c);

            row->addWidget(a);
            row->addWidget(b);
            row->addWidget(c);
            row->addStretch();
            mainLayout->addLayout(row);
        }

        mainLayout->addWidget(createTitle("尺寸"));
        {
            QHBoxLayout *row = new QHBoxLayout();
            row->setSpacing(16);

            QButtonGroup *group = new QButtonGroup(this);
            QelRadio *large = new QelRadio("Large", true, false, true, QelRadio::Size::Large, QelRadio::StyleType::Default, this);
            QelRadio *normal = new QelRadio("Default", false, false, true, QelRadio::Size::Default, QelRadio::StyleType::Default, this);
            QelRadio *small = new QelRadio("Small", false, false, true, QelRadio::Size::Small, QelRadio::StyleType::Default, this);
            group->addButton(large);
            group->addButton(normal);
            group->addButton(small);

            row->addWidget(large);
            row->addWidget(normal);
            row->addWidget(small);
            row->addStretch();
            mainLayout->addLayout(row);
        }

        mainLayout->addStretch();
    }

private:
    QLabel *createTitle(const QString &text)
    {
        QLabel *title = new QLabel(text, this);
        title->setStyleSheet("QLabel { color: #303133; font-size: 14px; font-weight: 600; }");
        return title;
    }
};

#endif // QELRADIOTESTER_H
