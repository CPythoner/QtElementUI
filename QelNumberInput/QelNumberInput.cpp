#include "QelNumberInput.h"

#include <QEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <limits>

namespace qel {

QelNumberInput::QelNumberInput(QWidget *parent,
                               int minValue,
                               int maxValue,
                               double initialValue,
                               double step,
                               bool readonly,
                               bool disabled,
                               bool controls,
                               ControlsPosition controlsPosition,  // 修改为枚举类型
                               const QString &placeholder)
    : QWidget(parent),
    minValue(minValue),
    maxValue(maxValue),
    currentValue(initialValue),
    step(step),
    readonly(readonly),
    disabled(disabled),
    controls(controls),
    controlsPosition(controlsPosition),
    size(Size::Default),
    precision(0)
{
    // 创建按钮和显示框
    decreaseButton = new QPushButton("-", this);
    increaseButton = new QPushButton("+", this);
    valueDisplay = new QLineEdit(QString::number(initialValue, 'f', precision), this);

    // 设置默认按钮大小为正方形，并根据 size 设置整体大小
    setSize(size);

    // 设置 QLineEdit
    valueDisplay->setReadOnly(readonly);
    valueDisplay->setAlignment(Qt::AlignCenter);
    valueDisplay->setPlaceholderText(placeholder);

    // 设置按钮和输入框的大小策略
    decreaseButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    increaseButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    valueDisplay->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    valueDisplay->setStyleSheet("QLineEdit { border-top: 1px solid #dcdfe6; border-bottom: 1px solid #dcdfe6; "
        "border-left: 0px; border-right: 0px; background-color: white; }");

    // 设置布局
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    setControlsPosition(controlsPosition);  // 根据传入参数设置布局

    setLayout(layout);

            // 连接信号槽
    connect(decreaseButton, &QPushButton::clicked, this, &QelNumberInput::onDecrease);
    connect(increaseButton, &QPushButton::clicked, this, &QelNumberInput::onIncrease);

            // 初始状态更新
    setDisabled(disabled);
    updateControlsState();
}

void QelNumberInput::setControlsPosition(ControlsPosition position) {
    controlsPosition = position;

    QString decreaseButtonStyle;
    QString increaseButtonStyle;

    QLayout *currentLayout = this->layout();
    if (currentLayout) {
        delete currentLayout;  // 清除当前布局，防止布局冲突
    }

    setSize(size);

    QVBoxLayout *rightLayout = nullptr;
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    if (controlsPosition == ControlsPosition::Right) {
        decreaseButtonStyle = "QPushButton { border: 1px solid #dcdfe6; background-color: #f5f7fa; "
            "border-bottom-right-radius: 6px; }"
            "QPushButton:pressed { background-color: #e6e9ef; }"
            "QPushButton:hover { border-color: #409EFF; color: #409EFF; }";
        increaseButtonStyle = "QPushButton { border: 1px solid #dcdfe6; background-color: #f5f7fa; "
            "border-top-right-radius: 6px; }"
            "QPushButton:pressed { background-color: #e6e9ef; }"
            "QPushButton:hover { border-color: #409EFF; color: #409EFF; }";
        rightLayout = new QVBoxLayout();
        rightLayout->setSpacing(0);
        rightLayout->setContentsMargins(0, 0, 0, 0);
        rightLayout->addWidget(increaseButton);
        rightLayout->addWidget(decreaseButton);
        layout->addWidget(valueDisplay);
        layout->addLayout(rightLayout);
    } else {
        decreaseButtonStyle = "QPushButton { border: 1px solid #dcdfe6; background-color: #f5f7fa; "
            "border-top-left-radius: 6px; border-bottom-left-radius: 6px; }"
            "QPushButton:pressed { background-color: #e6e9ef; }"
            "QPushButton:hover { border-color: #409EFF; color: #409EFF; }";
        increaseButtonStyle = "QPushButton { border: 1px solid #dcdfe6; background-color: #f5f7fa; "
            "border-top-right-radius: 6px; border-bottom-right-radius: 6px; }"
            "QPushButton:pressed { background-color: #e6e9ef; }"
            "QPushButton:hover { border-color: #409EFF; color: #409EFF; }";
        layout->addWidget(decreaseButton);
        layout->addWidget(valueDisplay);
        layout->addWidget(increaseButton);
    }

    decreaseButton->setStyleSheet(decreaseButtonStyle);
    increaseButton->setStyleSheet(increaseButtonStyle);
    setLayout(layout);
}

void QelNumberInput::setSize(Size size) {
    this->size = size;
    int buttonWidth;
    int buttonHeight;
    int widgetHeight;
    int widgetWidth = 0;
    int fontSize;

    switch (size) {
    case Size::Small:
        buttonWidth = 26;
        buttonHeight = buttonWidth; // 默认情况下，按钮是正方形
        widgetHeight = buttonWidth;
        fontSize = 14;
        break;
    case Size::Default:
        buttonWidth = 38;
        buttonHeight = buttonWidth; // 默认情况下，按钮是正方形
        widgetHeight = buttonWidth;
        fontSize = 16;
        break;
    case Size::Large:
        buttonWidth = 42;
        buttonHeight = buttonWidth; // 默认情况下，按钮是正方形
        widgetHeight = buttonWidth;
        fontSize = 18;
        break;
    }

    // 如果 controlsPosition 为 LeftRight，则调整按钮的高度为宽度的一半
    if (controlsPosition == ControlsPosition::Right) {
        buttonHeight = buttonWidth / 2;
        widgetHeight = buttonHeight * 2;
    }

    // 设置加减按钮的大小
    decreaseButton->setFixedSize(buttonWidth, buttonHeight);
    increaseButton->setFixedSize(buttonWidth, buttonHeight);
    valueDisplay->setFixedHeight(buttonWidth);

    // 确保控件的整体宽度合适
    int displayWidth = buttonWidth * 3;
    if (controlsPosition == ControlsPosition::Right) {
        widgetWidth = displayWidth + buttonWidth;
    } else if (controlsPosition == ControlsPosition::Default) {
        widgetWidth = buttonWidth * 2 + displayWidth ;
    }

    setFixedSize(widgetWidth, widgetHeight);  // 设置整个控件的大小

    // 设置按钮的字体大小
    QFont font = decreaseButton->font();
    font.setPointSize(fontSize);
    decreaseButton->setFont(font);
    increaseButton->setFont(font);
}


double QelNumberInput::value() const {
    return currentValue;
}

void QelNumberInput::setValue(double value) {
    if (value >= minValue && value <= maxValue) {
        currentValue = value;
        updateDisplay();
        emit valueChanged(currentValue);
    }
}

void QelNumberInput::setMinValue(int minValue) {
    this->minValue = minValue;
}

void QelNumberInput::setMaxValue(int maxValue) {
    this->maxValue = maxValue;
}

void QelNumberInput::setStep(double step) {
    this->step = step;
}

void QelNumberInput::setReadonly(bool readonly) {
    this->readonly = readonly;
    valueDisplay->setReadOnly(readonly);
}

void QelNumberInput::setDisabled(bool disabled) {
    this->disabled = disabled;
    setEnabled(!disabled);
    updateControlsState();
}

void QelNumberInput::setPlaceholder(const QString &placeholder) {
    valueDisplay->setPlaceholderText(placeholder);
}

void QelNumberInput::setPrecision(int precision) {
    this->precision = precision;
    updateDisplay();
}

void QelNumberInput::onIncrease() {
    if (currentValue + step <= maxValue) {
        currentValue += step;
        updateDisplay();
        emit valueChanged(currentValue);
        emit increaseIconClicked();
    }
}

void QelNumberInput::onDecrease() {
    if (currentValue - step >= minValue) {
        currentValue -= step;
        updateDisplay();
        emit valueChanged(currentValue);
        emit decreaseIconClicked();
    }
}

void QelNumberInput::updateDisplay() {
    valueDisplay->setText(QString::number(currentValue, 'f', precision));
}

void QelNumberInput::updateControlsState() {
    decreaseButton->setEnabled(!disabled && controls);
    increaseButton->setEnabled(!disabled && controls);
}

}
