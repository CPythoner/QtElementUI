#ifndef QELCHECKBOXTESTER_H
#define QELCHECKBOXTESTER_H

#include "QelCheckbox.h"

#include <QHBoxLayout>
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
        mainLayout->setSpacing(16);

        mainLayout->addWidget(createTitle("基础用法"));
        {
            QHBoxLayout *row = new QHBoxLayout();
            row->setSpacing(16);

            QelCheckbox *c1 = new QelCheckbox("Option 1", this);
            QelCheckbox *c2 = new QelCheckbox("Option 2", this);
            QelCheckbox *c3 = new QelCheckbox("Option 3", this);
            c1->setChecked(true);

            row->addWidget(c1);
            row->addWidget(c2);
            row->addWidget(c3);
            row->addStretch();
            mainLayout->addLayout(row);
        }

        mainLayout->addWidget(createTitle("禁用状态"));
        {
            QHBoxLayout *row = new QHBoxLayout();
            row->setSpacing(16);

            QelCheckbox *uncheckedDisabled = new QelCheckbox("Disabled", this);
            uncheckedDisabled->setDisabled(true);

            QelCheckbox *checkedDisabled = new QelCheckbox("Disabled Checked", this);
            checkedDisabled->setChecked(true);
            checkedDisabled->setDisabled(true);

            row->addWidget(uncheckedDisabled);
            row->addWidget(checkedDisabled);
            row->addStretch();
            mainLayout->addLayout(row);
        }

        mainLayout->addWidget(createTitle("不确定状态"));
        {
            QHBoxLayout *row = new QHBoxLayout();
            row->setSpacing(16);

            QelCheckbox *indeterminate = new QelCheckbox("Indeterminate", this);
            indeterminate->setIndeterminate(true);

            QelCheckbox *small = new QelCheckbox("Small", this);
            small->setSize(QelCheckbox::Size::Small);

            QelCheckbox *large = new QelCheckbox("Large", this);
            large->setSize(QelCheckbox::Size::Large);

            row->addWidget(indeterminate);
            row->addWidget(small);
            row->addWidget(large);
            row->addStretch();
            mainLayout->addLayout(row);
        }

        mainLayout->addWidget(createTitle("Check all（参考 Element Plus）"));
        {
            QVBoxLayout *groupLayout = new QVBoxLayout();
            groupLayout->setSpacing(8);

            QelCheckbox *checkAll = new QelCheckbox("Check all", this);
            QelCheckbox *a = new QelCheckbox("Shanghai", this);
            QelCheckbox *b = new QelCheckbox("Beijing", this);
            QelCheckbox *c = new QelCheckbox("Guangzhou", this);

            QList<QelCheckbox *> children = {a, b, c};

            auto refreshMaster = [checkAll, children]() {
                int checkedCount = 0;
                for (QelCheckbox *item : children) {
                    if (item->isChecked()) {
                        ++checkedCount;
                    }
                }

                checkAll->blockSignals(true);
                if (checkedCount == 0) {
                    checkAll->setIndeterminate(false);
                    checkAll->setChecked(false);
                } else if (checkedCount == children.size()) {
                    checkAll->setIndeterminate(false);
                    checkAll->setChecked(true);
                } else {
                    checkAll->setIndeterminate(true);
                }
                checkAll->blockSignals(false);
            };

            connect(checkAll, &QCheckBox::clicked, this, [children, checkAll]() {
                const bool checked = checkAll->isChecked();
                for (QelCheckbox *item : children) {
                    item->setChecked(checked);
                }
            });

            for (QelCheckbox *item : children) {
                connect(item, &QCheckBox::stateChanged, this, [refreshMaster](int) {
                    refreshMaster();
                });
                groupLayout->addWidget(item);
            }

            refreshMaster();
            groupLayout->insertWidget(0, checkAll);
            mainLayout->addLayout(groupLayout);
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

#endif // QELCHECKBOXTESTER_H
