#include "QelNumberInput.h"

#include <QEvent>
#include <QHBoxLayout>
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
                               const QString &placeholder)
    : QWidget(parent),
    minValue(minValue),
    maxValue(maxValue),
    currentValue(initialValue),
    step(step),
    readonly(readonly),
    disabled(disabled),
    controls(controls),
    size(Default),
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

            // 设置样式表，添加圆角，并设置焦点和 hover 样式
    QString decreaseButtonStyle = "QPushButton { border: 1px solid #dcdfe6; background-color: #f5f7fa; "
        "border-top-left-radius: 4px; border-bottom-left-radius: 6px; }"
        "QPushButton:pressed { background-color: #e6e9ef; }"
        "QPushButton:hover { border-color: #409EFF; color: #409EFF; }";
    QString increaseButtonStyle = "QPushButton { border: 1px solid #dcdfe6; background-color: #f5f7fa; "
        "border-top-right-radius: 4px; border-bottom-right-radius: 6px; }"
        "QPushButton:pressed { background-color: #e6e9ef; }"
        "QPushButton:hover { border-color: #409EFF; color: #409EFF; }";
    decreaseButton->setStyleSheet(decreaseButtonStyle);
    increaseButton->setStyleSheet(increaseButtonStyle);

    valueDisplay->setStyleSheet("QLineEdit { border-top: 1px solid #dcdfe6; border-bottom: 1px solid #dcdfe6; "
        "border-left: 0px; border-right: 0px; background-color: white; }");

            // 设置布局
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(decreaseButton);
    layout->addWidget(valueDisplay);
    layout->addWidget(increaseButton);
    setLayout(layout);

            // 连接信号槽
    connect(decreaseButton, &QPushButton::clicked, this, &QelNumberInput::onDecrease);
    connect(increaseButton, &QPushButton::clicked, this, &QelNumberInput::onIncrease);

            // 初始状态更新
    setDisabled(disabled);
    updateControlsState();
}

bool QelNumberInput::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::FocusIn) {
        setStyleSheet("QWidget { border: 1px solid #409EFF; }");
        qDebug() << "Focus In Event Triggered";
        return true;
    } else if (event->type() == QEvent::FocusOut) {
        setStyleSheet("QWidget { border: 1px solid #dcdfe6; }");
        qDebug() << "Focus Out Event Triggered";
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void QelNumberInput::setSize(Size size) {
    this->size = size;
    int buttonSize;
    int widgetHeight;
    int widgetWidth;
    int fontSize;

    switch (size) {
    case Small:
        buttonSize = 26;
        widgetHeight = buttonSize;
        widgetWidth = buttonSize * 5;
        fontSize = 14;
        break;
    case Default:
        buttonSize = 38;
        widgetHeight = buttonSize;
        widgetWidth = buttonSize * 5;
        fontSize = 16;
        break;
    case Large:
        buttonSize = 42;
        widgetHeight = buttonSize;
        widgetWidth = buttonSize * 5;
        fontSize = 18;
        break;
    }

            // 设置加减按钮为正方形，并调整整体大小
    decreaseButton->setFixedSize(buttonSize, buttonSize);
    increaseButton->setFixedSize(buttonSize, buttonSize);
    valueDisplay->setFixedHeight(buttonSize);
    valueDisplay->setFixedWidth(buttonSize*3);

            // 设置按钮的字体大小
    QFont font = decreaseButton->font();
    font.setPointSize(fontSize);
    decreaseButton->setFont(font);
    increaseButton->setFont(font);

    setFixedSize(widgetWidth, widgetHeight);  // 设置整个控件的大小
}

void QelNumberInput::onFocusIn() {
    setStyleSheet("QWidget { border: 1px solid #409EFF; }");
    qDebug() << "onFocusIn";
}

void QelNumberInput::onFocusOut() {
    setStyleSheet("QWidget { border: 1px solid #dcdfe6; }");
}

void QelNumberInput::focusInEvent(QFocusEvent *event) {
    QWidget::focusInEvent(event);
    setStyleSheet("QWidget { border: 1px solid #409EFF; }");
    qDebug() << "onFocusIn";
}

void QelNumberInput::focusOutEvent(QFocusEvent *event) {
    QWidget::focusOutEvent(event);
    setStyleSheet("QWidget { border: 1px solid #dcdfe6; }");
}

void QelNumberInput::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);  // 从当前 widget 初始化 opt

    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
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
    decreaseButton->setVisible(controls);
    increaseButton->setVisible(controls);
    if (!controls) {
        valueDisplay->setFixedWidth(size == Large ? 5 * 42 : size == Default ? 5 * 38 : 5 * 26); // 修改宽度以适应无控制按钮状态
    }
    decreaseButton->setEnabled(!disabled && controls);
    increaseButton->setEnabled(!disabled && controls);
}

}
