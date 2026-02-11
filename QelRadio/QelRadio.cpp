#include "QelRadio.h"

namespace qel {

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
        indicatorSize = 14;
        fontSize = 14;
        spacing = 8;
        minHeight = 32;
        horizontalPadding = 14;
        break;
    case Size::Small:
        indicatorSize = 12;
        fontSize = 12;
        spacing = 6;
        minHeight = 24;
        horizontalPadding = 10;
        break;
    }

    if (styleType_ == StyleType::Button) {
        setStyleSheet(QString(
            "QRadioButton {"
            " color: #606266;"
            " font-size: %1px;"
            " min-height: %2px;"
            " padding-left: %3px;"
            " padding-right: %3px;"
            " border: 1px solid #DCDFE6;"
            " border-radius: 4px;"
            " background: #FFFFFF;"
            "}"
            "QRadioButton::indicator { width: 0px; height: 0px; }"
            "QRadioButton:hover {"
            " color: #409EFF;"
            " border-color: #409EFF;"
            "}"
            "QRadioButton:checked {"
            " color: #409EFF;"
            " border-color: #409EFF;"
            " background: #ECF5FF;"
            "}"
            "QRadioButton:disabled {"
            " color: #C0C4CC;"
            " border-color: #EBEEF5;"
            " background: #F5F7FA;"
            "}"
        ).arg(fontSize).arg(minHeight).arg(horizontalPadding));
        return;
    }

    QString controlStyle;
    if (border_) {
        controlStyle = QString(
            " border: 1px solid #DCDFE6;"
            " border-radius: 4px;"
            " background: #FFFFFF;"
            " min-height: %1px;"
            " padding-left: %2px;"
            " padding-right: %2px;"
        ).arg(minHeight).arg(horizontalPadding);
    }

    setStyleSheet(QString(
        "QRadioButton {"
        " color: #606266;"
        " spacing: %1px;"
        " font-size: %2px;"
        "%3"
        "}"
        "QRadioButton:hover {"
        " color: #409EFF;"
        "%4"
        "}"
        "QRadioButton:checked {"
        " color: #409EFF;"
        "%5"
        "}"
        "QRadioButton:disabled {"
        " color: #C0C4CC;"
        "%6"
        "}"
        "QRadioButton::indicator {"
        " width: %7px;"
        " height: %7px;"
        " border-radius: %8px;"
        " border: 1px solid #DCDFE6;"
        " background: #FFFFFF;"
        "}"
        "QRadioButton::indicator:hover {"
        " border: 1px solid #409EFF;"
        "}"
        "QRadioButton::indicator:checked {"
        " border: 5px solid #409EFF;"
        " background: #FFFFFF;"
        "}"
        "QRadioButton::indicator:checked:disabled {"
        " border: 5px solid #B3D8FF;"
        "}"
        "QRadioButton::indicator:disabled {"
        " border: 1px solid #E4E7ED;"
        " background: #F5F7FA;"
        "}"
    )
        .arg(spacing)
        .arg(fontSize)
        .arg(controlStyle)
        .arg(border_ ? " border-color: #409EFF;" : "")
        .arg(border_ ? " border-color: #409EFF; background: #ECF5FF;" : "")
        .arg(border_ ? " border-color: #EBEEF5; background: #F5F7FA;" : "")
        .arg(indicatorSize)
        .arg(indicatorSize / 2));
}

} // namespace qel
