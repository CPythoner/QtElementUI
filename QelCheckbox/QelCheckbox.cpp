#include "QelCheckbox.h"

namespace qel {

QelCheckbox::QelCheckbox(const QString &text, QWidget *parent)
    : QCheckBox(text, parent)
{
    setTristate(true);
    setCheckState(Qt::Unchecked);

    connect(this, &QCheckBox::stateChanged, this, [this](int) {
        applyStyle();
    });

    applyStyle();
}

void QelCheckbox::setSize(Size size)
{
    size_ = size;
    applyStyle();
}

void QelCheckbox::setIndeterminate(bool indeterminate)
{
    setCheckState(indeterminate ? Qt::PartiallyChecked : (isChecked() ? Qt::Checked : Qt::Unchecked));
    applyStyle();
}

void QelCheckbox::applyStyle()
{
    int indicatorSize = 14;
    int fontSize = 14;
    int spacing = 8;

    switch (size_) {
    case Size::Large:
        indicatorSize = 16;
        fontSize = 16;
        spacing = 10;
        break;
    case Size::Default:
        indicatorSize = 14;
        fontSize = 14;
        spacing = 8;
        break;
    case Size::Small:
        indicatorSize = 12;
        fontSize = 12;
        spacing = 6;
        break;
    }

    setStyleSheet(QString(
        "QCheckBox {"
        " color: #606266;"
        " spacing: %1px;"
        " font-size: %2px;"
        "}"
        "QCheckBox:disabled {"
        " color: #C0C4CC;"
        "}"
        "QCheckBox::indicator {"
        " width: %3px;"
        " height: %3px;"
        " border: 1px solid #DCDFE6;"
        " border-radius: 2px;"
        " background: #FFFFFF;"
        "}"
        "QCheckBox::indicator:hover {"
        " border: 1px solid #409EFF;"
        "}"
        "QCheckBox::indicator:checked {"
        " border: 1px solid #409EFF;"
        " background: #409EFF;"
        " image: url(none);"
        "}"
        "QCheckBox::indicator:indeterminate {"
        " border: 1px solid #409EFF;"
        " background: #409EFF;"
        "}"
        "QCheckBox::indicator:disabled {"
        " border: 1px solid #E4E7ED;"
        " background: #F5F7FA;"
        "}"
        "QCheckBox::indicator:checked:disabled,"
        "QCheckBox::indicator:indeterminate:disabled {"
        " border: 1px solid #B3D8FF;"
        " background: #B3D8FF;"
        "}"
    ).arg(spacing).arg(fontSize).arg(indicatorSize));
}

} // namespace qel
