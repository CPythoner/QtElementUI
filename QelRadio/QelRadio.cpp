#include "QelRadio.h"

namespace qel {

QelRadio::QelRadio(const QString &text, QWidget *parent)
    : QRadioButton(text, parent)
{
    applyStyle();
}

void QelRadio::setSize(Size size)
{
    size_ = size;
    applyStyle();
}

void QelRadio::applyStyle()
{
    int indicatorSize = 14;
    int dotMargin = 4;
    int fontSize = 14;
    int spacing = 8;

    switch (size_) {
    case Size::Large:
        indicatorSize = 16;
        dotMargin = 5;
        fontSize = 16;
        spacing = 10;
        break;
    case Size::Default:
        indicatorSize = 14;
        dotMargin = 4;
        fontSize = 14;
        spacing = 8;
        break;
    case Size::Small:
        indicatorSize = 12;
        dotMargin = 3;
        fontSize = 12;
        spacing = 6;
        break;
    }

    setStyleSheet(QString(
        "QRadioButton {"
        " color: #606266;"
        " spacing: %1px;"
        " font-size: %2px;"
        "}"
        "QRadioButton:disabled {"
        " color: #C0C4CC;"
        "}"
        "QRadioButton::indicator {"
        " width: %3px;"
        " height: %3px;"
        " border-radius: %4px;"
        " border: 1px solid #DCDFE6;"
        " background: #FFFFFF;"
        "}"
        "QRadioButton::indicator:hover {"
        " border: 1px solid #409EFF;"
        "}"
        "QRadioButton::indicator:checked {"
        " border: 1px solid #409EFF;"
        " background: #FFFFFF;"
        "}"
        "QRadioButton::indicator:checked {"
        " image: none;"
        "}"
        "QRadioButton::indicator:checked:disabled {"
        " border: 1px solid #B3D8FF;"
        "}"
        "QRadioButton::indicator:disabled {"
        " border: 1px solid #E4E7ED;"
        " background: #F5F7FA;"
        "}"
    ).arg(spacing).arg(fontSize).arg(indicatorSize).arg(indicatorSize / 2));

    setStyleSheet(styleSheet() + QString(
        "QRadioButton::indicator:checked {"
        " background-color: #409EFF;"
        " border: %1px solid #409EFF;"
        "}"
        "QRadioButton::indicator:checked:disabled {"
        " background-color: #B3D8FF;"
        " border: %1px solid #B3D8FF;"
        "}"
    ).arg(dotMargin));
}

} // namespace qel
