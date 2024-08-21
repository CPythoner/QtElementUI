#ifndef QELNUMBERINPUTTESTER_H
#define QELNUMBERINPUTTESTER_H

#include "QelNumberInput.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

using qel::QelNumberInput;

class QelNumberInputTester : public QWidget {
    Q_OBJECT

public:
    explicit QelNumberInputTester(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        // 基础用法
        mainLayout->addWidget(createNumberInput("基础用法", 0, 100, 5, 1, false, false, true));

        // 禁用状态
        mainLayout->addWidget(createNumberInput("禁用状态", 0, 10, 1, 1, false, true, true));

        // 严格步进
        mainLayout->addWidget(createNumberInput("严格步进", 0, 100, 18, 10, true, false, true));

        // 精度
        mainLayout->addWidget(createNumberInput("精度", 0, 100, 1.5, 0.1, false, false, true, 2));

        // 不同尺寸
        mainLayout->addWidget(createSizedNumberInput("不同尺寸"));

        // 不同尺寸，没有控制按钮、
        mainLayout->addWidget(createSizedNoControlNumberInput("不同尺寸&无控制按钮"));

        // 按钮位置
        mainLayout->addWidget(createControlsPositionNumberInput("按钮位置"));

        setLayout(mainLayout);
    }

private:
    QWidget* createNumberInput(const QString &labelText, int minValue, int maxValue, double initialValue, double step,
                               bool stepStrictly = false, bool disabled = false, bool controls = true, int precision = 0) {
        QWidget *widget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(widget);

        QLabel *label = new QLabel(labelText, widget);
        QelNumberInput *numberInput = new QelNumberInput(widget, minValue, maxValue, initialValue, step);
        numberInput->setReadonly(false);
        numberInput->setDisabled(disabled);
        numberInput->setPrecision(precision);

        layout->addWidget(label);
        layout->addWidget(numberInput);
        layout->setSpacing(10);
        layout->setContentsMargins(20, 20, 20, 20);

        return widget;
    }

    QWidget* createSizedNumberInput(const QString &labelText) {
        QWidget *widget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(widget);

        QLabel *label = new QLabel(labelText, widget);
        QHBoxLayout *sizesLayout = new QHBoxLayout();

        QelNumberInput *smallInput = new QelNumberInput(widget, 0, 10, 1, 1);
        smallInput->setSize(QelNumberInput::Size::Small);

        QelNumberInput *defaultInput = new QelNumberInput(widget, 0, 10, 2, 1);
        defaultInput->setSize(QelNumberInput::Size::Default);

        QelNumberInput *largeInput = new QelNumberInput(widget, 0, 10, 3, 1);
        largeInput->setSize(QelNumberInput::Size::Large);

        sizesLayout->addWidget(smallInput);
        sizesLayout->addWidget(defaultInput);
        sizesLayout->addWidget(largeInput);

        layout->addWidget(label);
        layout->addLayout(sizesLayout);

        return widget;
    }

    QWidget* createControlsPositionNumberInput(const QString &labelText) {
        QWidget *widget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(widget);

        QLabel *label = new QLabel(labelText, widget);
        QHBoxLayout *controlsLayout = new QHBoxLayout();

        QelNumberInput *leftInput = new QelNumberInput(widget, 0, 10, 1, 1);
        leftInput->setControlsPosition(QelNumberInput::ControlsPosition::Default);

        QelNumberInput *rightInput = new QelNumberInput(widget, 0, 10, 1, 1);
        rightInput->setControlsPosition(QelNumberInput::ControlsPosition::Right);

        controlsLayout->addWidget(leftInput);
        controlsLayout->addWidget(rightInput);

        layout->addWidget(label);
        layout->addLayout(controlsLayout);

        return widget;
    }

    QWidget* createSizedNoControlNumberInput(const QString &labelText) {
        QWidget *widget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(widget);

        QLabel *label = new QLabel(labelText, widget);
        QHBoxLayout *sizesLayout = new QHBoxLayout();

        QelNumberInput *smallInput = new QelNumberInput(widget, 0, 10, 1, 1, false, false, false);
        smallInput->setSize(QelNumberInput::Size::Small);

        QelNumberInput *defaultInput = new QelNumberInput(widget, 0, 10, 2, 1, false, false, false);
        defaultInput->setSize(QelNumberInput::Size::Default);

        QelNumberInput *largeInput = new QelNumberInput(widget, 0, 10, 3, 1, false, false, false);
        largeInput->setSize(QelNumberInput::Size::Large);

        sizesLayout->addWidget(smallInput);
        sizesLayout->addWidget(defaultInput);
        sizesLayout->addWidget(largeInput);

        layout->addWidget(label);
        layout->addLayout(sizesLayout);

        return widget;
    }

};

#endif // QELNUMBERINPUTTESTER_H
