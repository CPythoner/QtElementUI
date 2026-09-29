#include "QelRadio.h"

#include "../QelStyleHelper/QelStyleHelper.h"
#include "../QelTheme/QelTheme.h"

namespace qel {

namespace {

QelStyleHelper::StateStyleSet radioOuterStateStyles(bool bordered)
{
    const QelTheme::ColorTokens &c = QelTheme::colors();

    const QString normalBorder = bordered ? c.borderBase : "transparent";
    const QString hoverBorder = bordered ? c.primary : "transparent";
    const QString disabledBorder = bordered ? c.borderLighter : "transparent";
    const QString normalBackground = bordered ? c.fillBlank : "transparent";
    const QString disabledBackground = bordered ? c.fillLight : "transparent";

    return {
        {normalBackground, c.textRegular, normalBorder},
        {normalBackground, c.primary, hoverBorder},
        {normalBackground, c.primary, hoverBorder},
        {normalBackground, c.primary, hoverBorder},
        {disabledBackground, c.textPlaceholder, disabledBorder},
        {disabledBackground, c.textPlaceholder, disabledBorder}
    };
}

} // namespace

QelRadio::QelRadio(const QString &text, QWidget *parent)
    : QelRadio(text, false, false, false, Size::Default, StyleType::Default, parent)
{
}

QelRadio::QelRadio(const QString &text,
                   bool checked,
                   bool disabled,
                   bool border,
                   Size size,
                   StyleType styleType,
                   QWidget *parent)
    : QRadioButton(text, parent),
      size_(size),
      border_(border),
      styleType_(styleType)
{
    setChecked(checked);
    setDisabled(disabled);
    setCursor(Qt::PointingHandCursor);

    applyStyle();
}

void QelRadio::setSize(Size size)
{
    if (size_ == size) {
        return;
    }

    size_ = size;
    applyStyle();
}

void QelRadio::setBorder(bool border)
{
    if (border_ == border) {
        return;
    }

    border_ = border;
    applyStyle();
}

void QelRadio::setStyleType(StyleType styleType)
{
    if (styleType_ == styleType) {
        return;
    }

    styleType_ = styleType;
    applyStyle();
}

void QelRadio::applyStyle()
{
    int indicatorSize = 14;
    int fontSize = 14;
    int spacing = 8;
    int minHeight = 32;
    int horizontalPadding = 14;

    switch (size_) {
    case Size::Large:
        indicatorSize = 16;
        fontSize = 14;
        spacing = 10;
        minHeight = 40;
        horizontalPadding = 18;
        break;
    case Size::Default:
        break;
    case Size::Small:
        indicatorSize = 12;
        fontSize = 12;
        spacing = 6;
        minHeight = 24;
        horizontalPadding = 10;
        break;
    }

    const QelTheme::ColorTokens &c = QelTheme::colors();
    const bool bordered = border_ || styleType_ == StyleType::Button;

    QString style = QelStyleHelper::composeStateStyleSheet(
        "QRadioButton",
        QString(),
        radioOuterStateStyles(bordered),
        true);

    style += QString(
        "QRadioButton {"
        " font-size: %1px;"
        " min-height: %2px;"
        " padding-left: %3px;"
        " padding-right: %3px;"
        " border-radius: 4px;"
        "}"
    ).arg(fontSize).arg(minHeight).arg(horizontalPadding);

    if (styleType_ == StyleType::Button) {
        style += QString(
            "QRadioButton::indicator { width: 0px; height: 0px; }"
            "QRadioButton:checked {"
            " color: %1;"
            " border-color: %1;"
            " background: %2;"
            "}"
        ).arg(c.primary, c.primaryLight);

        setStyleSheet(style);
        return;
    }

    style += QString(
        "QRadioButton { spacing: %1px; }"
        "QRadioButton:checked {"
        " color: %2;"
        "%3"
        "}"
        "QRadioButton::indicator {"
        " width: %4px;"
        " height: %4px;"
        " border-radius: %5px;"
        " border: 1px solid %6;"
        " background: %7;"
        "}"
        "QRadioButton::indicator:hover {"
        " border: 1px solid %2;"
        "}"
        "QRadioButton::indicator:checked {"
        " border: 5px solid %2;"
        " background: %7;"
        "}"
        "QRadioButton::indicator:checked:disabled {"
        " border: 5px solid %8;"
        "}"
        "QRadioButton::indicator:disabled {"
        " border: 1px solid %9;"
        " background: %10;"
        "}"
    )
        .arg(spacing)
        .arg(c.primary)
        .arg(border_
                 ? QString(" border-color: %1; background: %2;")
                       .arg(c.primary, c.primaryLight)
                 : QString())
        .arg(indicatorSize)
        .arg(indicatorSize / 2)
        .arg(c.borderBase)
        .arg(c.fillBlank)
        .arg(c.primaryDisabled)
        .arg(c.borderLight)
        .arg(c.fillLight);

    setStyleSheet(style);
}

} // namespace qel
