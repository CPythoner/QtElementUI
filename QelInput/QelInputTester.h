#ifndef QELINPUTTESTER_H
#define QELINPUTTESTER_H

#include "QelInput.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

using qel::QelInput;

class QelInputTester : public QWidget {
public:
    explicit QelInputTester(QWidget *parent = nullptr) : QWidget(parent)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(16);

        mainLayout->addWidget(createCase("基础输入", []() {
            QelInput *input = new QelInput(nullptr, QelInput::Type::Text, "请输入内容");
            input->setClearable(true);
            return input;
        }));

        mainLayout->addWidget(createCase("密码输入（显示密码）", []() {
            QelInput *input = new QelInput(nullptr, QelInput::Type::Password, "请输入密码");
            input->setShowPassword(true);
            return input;
        }));

        mainLayout->addWidget(createCase("禁用状态", []() {
            QelInput *input = new QelInput(nullptr, QelInput::Type::Text, "禁用状态", "不可编辑");
            input->setDisabled(true);
            return input;
        }));

        mainLayout->addWidget(createCase("不同尺寸", []() {
            QWidget *container = new QWidget();
            QVBoxLayout *layout = new QVBoxLayout(container);

            QelInput *large = new QelInput(nullptr, QelInput::Type::Text, "Large 尺寸");
            large->setSize(QelInput::Size::Large);

            QelInput *normal = new QelInput(nullptr, QelInput::Type::Text, "Default 尺寸");
            normal->setSize(QelInput::Size::Default);

            QelInput *small = new QelInput(nullptr, QelInput::Type::Text, "Small 尺寸");
            small->setSize(QelInput::Size::Small);

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

#endif // QELINPUTTESTER_H
