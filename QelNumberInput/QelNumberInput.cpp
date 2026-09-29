#include "QelNumberInput.h"

#include "../QelStyleHelper/QelStyleHelper.h"
#include "../QelTheme/QelTheme.h"

#include <QEvent>
#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>
#include <limits>

namespace qel {

namespace {

QelStyleHelper::StateStyleSet numberButtonStateStyles()
{
    const QelTheme::ColorTokens &c = QelTheme::colors();

    return {
        {c.fillLight, c.textRegular, c.borderBase},
        {c.primaryLight, c.primary, c.primary},
        {c.fillPressed, c.primary, c.primary},
        {c.primaryLight, c.primary, c.primary},
        {c.fillLight, c.textPlaceholder, c.borderLight},
        {c.fillLight, c.textPlaceholder, c.borderLight}
    };
}

QelStyleHelper::StateStyleSet numberInputStateStyles()
{
    const QelTheme::ColorTokens &c = QelTheme::colors();

    return {
        {c.fillBlank, c.textRegular, c.borderBase},
        {c.fillBlank, c.textRegular, c.textPlaceholder},
        {c.fillBlank, c.textRegular, c.primary},
        {c.fillBlank, c.textRegular, c.primary},
        {c.fillLight, c.textPlaceholder, c.borderLight},
        {c.fillLight, c.textPlaceholder, c.borderLight}
    };
}

} // namespace

QelNumberInput::QelNumberInput(QWidget *parent,
                               int minValue,
                               int maxValue,
                               double initialValue,
                               double step,
                               bool readonly,
                               bool disabled,
                               bool controls,
                               ControlsPosition controlsPosition,
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
    decreaseButton = new QPushButton("-", this);
    increaseButton = new QPushButton("+", this);
    valueDisplay = new QLineEdit(QString::number(initialValue, 'f', precision), this);

    setSize(size);

    valueDisplay->setReadOnly(readonly);
    valueDisplay->setAlignment(Qt::AlignCenter);
    valueDisplay->setPlaceholderText(placeholder);
    valueDisplay->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    decreaseButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    increaseButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QString inputStyle = QelStyleHelper::composeStateStyleSheet(
        "QLineEdit",
        QString(),
        numberInputStateStyles(),
        true);
    inputStyle +=
        "QLineEdit {"
        " border-left: 0px;"
        " border-right: 0px;"
        "}";
    valueDisplay->setStyleSheet(inputStyle);

    setControlsPosition(controlsPosition);

    connect(decreaseButton, &QPushButton::clicked, this, &QelNumberInput::onDecrease);
    connect(increaseButton, &QPushButton::clicked, this, &QelNumberInput::onIncrease);

    setDisabled(disabled);
    updateControlsState();
}

void QelNumberInput::setControlsPosition(ControlsPosition position)
{
    controlsPosition = position;

    QLayout *currentLayout = layout();
    if (currentLayout) {
        delete currentLayout;
    }

    setSize(size);

    QVBoxLayout *rightLayout = nullptr;
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QString decreaseButtonStyle = QelStyleHelper::composeStateStyleSheet(
        "QPushButton",
        QString(),
        numberButtonStateStyles(),
        true);
    QString increaseButtonStyle = decreaseButtonStyle;

    if (controlsPosition == ControlsPosition::Right) {
        decreaseButtonStyle +=
            "QPushButton {"
            " border-bottom-right-radius: 6px;"
            "}";
        increaseButtonStyle +=
            "QPushButton {"
            " border-top-right-radius: 6px;"
            "}";

        rightLayout = new QVBoxLayout();
        rightLayout->setSpacing(0);
        rightLayout->setContentsMargins(0, 0, 0, 0);
        rightLayout->addWidget(increaseButton);
        rightLayout->addWidget(decreaseButton);
        mainLayout->addWidget(valueDisplay);
        mainLayout->addLayout(rightLayout);
    } else {
        decreaseButtonStyle +=
            "QPushButton {"
            " border-top-left-radius: 6px;"
            " border-bottom-left-radius: 6px;"
            "}";
        increaseButtonStyle +=
            "QPushButton {"
            " border-top-right-radius: 6px;"
            " border-bottom-right-radius: 6px;"
            "}";

        mainLayout->addWidget(decreaseButton);
        mainLayout->addWidget(valueDisplay);
        mainLayout->addWidget(increaseButton);
    }

    decreaseButton->setStyleSheet(decreaseButtonStyle);
    increaseButton->setStyleSheet(increaseButtonStyle);
    setLayout(mainLayout);
}

void QelNumberInput::setSize(Size size)
{
    this->size = size;

    int buttonWidth;
    int buttonHeight;
    int widgetHeight;
    int widgetWidth = 0;
    int fontSize;

    switch (size) {
    case Size::Small:
        buttonWidth = 26;
        buttonHeight = buttonWidth;
        widgetHeight = buttonWidth;
        fontSize = 14;
        break;
    case Size::Default:
        buttonWidth = 38;
        buttonHeight = buttonWidth;
        widgetHeight = buttonWidth;
        fontSize = 16;
        break;
    case Size::Large:
        buttonWidth = 42;
        buttonHeight = buttonWidth;
        widgetHeight = buttonWidth;
        fontSize = 18;
        break;
    }

    if (controlsPosition == ControlsPosition::Right) {
        buttonHeight = buttonWidth / 2;
        widgetHeight = buttonHeight * 2;
    }

    decreaseButton->setFixedSize(buttonWidth, buttonHeight);
    increaseButton->setFixedSize(buttonWidth, buttonHeight);
    valueDisplay->setFixedHeight(buttonWidth);

    const int displayWidth = buttonWidth * 3;
    if (controlsPosition == ControlsPosition::Right) {
        widgetWidth = displayWidth + buttonWidth;
    } else if (controlsPosition == ControlsPosition::Default) {
        widgetWidth = buttonWidth * 2 + displayWidth;
    }

    setFixedSize(widgetWidth, widgetHeight);

    QFont font = decreaseButton->font();
    font.setPointSize(fontSize);
    decreaseButton->setFont(font);
    increaseButton->setFont(font);
}

double QelNumberInput::value() const
{
    return currentValue;
}

void QelNumberInput::setValue(double value)
{
    if (value >= minValue && value <= maxValue) {
        currentValue = value;
        updateDisplay();
        emit valueChanged(currentValue);
    }
}

void QelNumberInput::setMinValue(int minValue)
{
    this->minValue = minValue;
}

void QelNumberInput::setMaxValue(int maxValue)
{
    this->maxValue = maxValue;
}

void QelNumberInput::setStep(double step)
{
    this->step = step;
}

void QelNumberInput::setReadonly(bool readonly)
{
    this->readonly = readonly;
    valueDisplay->setReadOnly(readonly);
}

void QelNumberInput::setDisabled(bool disabled)
{
    this->disabled = disabled;
    setEnabled(!disabled);
    updateControlsState();
}

void QelNumberInput::setPlaceholder(const QString &placeholder)
{
    valueDisplay->setPlaceholderText(placeholder);
}

void QelNumberInput::setPrecision(int precision)
{
    this->precision = precision;
    updateDisplay();
}

void QelNumberInput::onIncrease()
{
    if (currentValue + step <= maxValue) {
        currentValue += step;
        updateDisplay();
        emit valueChanged(currentValue);
        emit increaseIconClicked();
    }
}

void QelNumberInput::onDecrease()
{
    if (currentValue - step >= minValue) {
        currentValue -= step;
        updateDisplay();
        emit valueChanged(currentValue);
        emit decreaseIconClicked();
    }
}

void QelNumberInput::updateDisplay()
{
    valueDisplay->setText(QString::number(currentValue, 'f', precision));
}

void QelNumberInput::updateControlsState()
{
    decreaseButton->setEnabled(!disabled && controls);
    increaseButton->setEnabled(!disabled && controls);
}

} // namespace qel
