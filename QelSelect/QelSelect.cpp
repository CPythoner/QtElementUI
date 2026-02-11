#include "QelSelect.h"
#include "../QelIcon/QelIcon.h"

#include <QAbstractItemView>
#include <QHBoxLayout>
#include <QLineEdit>

namespace qel {

QelSelect::QelSelect(QWidget *parent)
    : QWidget(parent),
      comboBox_(new QComboBox(this)),
      dropDownButton_(new QToolButton(this))
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(comboBox_);

    dropDownButton_->setCursor(Qt::PointingHandCursor);
    dropDownButton_->setFocusPolicy(Qt::NoFocus);
    connect(dropDownButton_, &QToolButton::clicked, comboBox_, &QComboBox::showPopup);

    connect(comboBox_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &QelSelect::currentIndexChanged);
    connect(comboBox_, &QComboBox::currentTextChanged,
            this, &QelSelect::currentTextChanged);

    applyStyle();
}

void QelSelect::setOptions(const QStringList &options)
{
    comboBox_->clear();
    comboBox_->addItems(options);
}

void QelSelect::addOption(const QString &label, const QVariant &value)
{
    if (value.isValid()) {
        comboBox_->addItem(label, value);
    } else {
        comboBox_->addItem(label, label);
    }
}

void QelSelect::clearOptions()
{
    comboBox_->clear();
}

void QelSelect::setCurrentValue(const QVariant &value)
{
    int index = comboBox_->findData(value);
    if (index < 0) {
        index = comboBox_->findText(value.toString());
    }

    if (index >= 0) {
        comboBox_->setCurrentIndex(index);
    }
}

QVariant QelSelect::currentValue() const
{
    return comboBox_->currentData();
}

QString QelSelect::currentText() const
{
    return comboBox_->currentText();
}

void QelSelect::setPlaceholder(const QString &placeholder)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    comboBox_->setPlaceholderText(placeholder);
#else
    comboBox_->setEditable(true);
    comboBox_->lineEdit()->setPlaceholderText(placeholder);
    comboBox_->setEditable(false);
#endif
}

void QelSelect::setDisabled(bool disabled)
{
    comboBox_->setDisabled(disabled);
    if (dropDownButton_ != nullptr) {
        dropDownButton_->setDisabled(disabled);
    }
}

void QelSelect::setSize(Size size)
{
    size_ = size;
    applyStyle();
}

void QelSelect::applyStyle()
{
    int height = 32;
    int fontSize = 14;
    int horizontalPadding = 12;
    int dropDownWidth = 38;

    switch (size_) {
    case Size::Large:
        height = 40;
        fontSize = 14;
        horizontalPadding = 14;
        dropDownWidth = 42;
        break;
    case Size::Default:
        height = 32;
        fontSize = 14;
        horizontalPadding = 12;
        dropDownWidth = 38;
        break;
    case Size::Small:
        height = 24;
        fontSize = 12;
        horizontalPadding = 8;
        dropDownWidth = 26;
        break;
    }

    QFont font = comboBox_->font();
    font.setPixelSize(fontSize);
    comboBox_->setFont(font);
    if (comboBox_->view()) {
        comboBox_->view()->setFont(font);
    }

    comboBox_->setFixedHeight(height);
    comboBox_->setStyleSheet(QString(
        "QComboBox {"
        " border: 1px solid #DCDFE6;"
        " border-radius: 4px;"
        " color: #606266;"
        " padding-left: %1px;"
        " padding-right: %3px;"
        "}"
        "QComboBox:focus {"
        " border: 1px solid #409EFF;"
        "}"
        "QComboBox::drop-down {"
        " width: 0px;"
        " border: 0px;"
        "}"
        "QComboBox::down-arrow {"
        " image: none;"
        "}"
        "QComboBox:disabled {"
        " color: #C0C4CC;"
        " background: #F5F7FA;"
        " border: 1px solid #E4E7ED;"
        "}"
        "QComboBox QAbstractItemView {"
        " border: 1px solid #E4E7ED;"
        " color: #606266;"
        " selection-background-color: #ECF5FF;"
        "}"
    ).arg(horizontalPadding).arg(dropDownWidth));

    dropDownButton_->setFixedSize(dropDownWidth, height);
    dropDownButton_->setStyleSheet(
        "QToolButton {"
        " border: 1px solid #DCDFE6;"
        " border-left: 0px;"
        " border-top-right-radius: 4px;"
        " border-bottom-right-radius: 4px;"
        " background-color: #F5F7FA;"
        "}"
        "QToolButton:hover {"
        " border-color: #409EFF;"
        " color: #409EFF;"
        " background-color: #ECF5FF;"
        "}"
        "QToolButton:disabled {"
        " border-color: #E4E7ED;"
        " color: #C0C4CC;"
        " background-color: #F5F7FA;"
        "}"
    );

    updateDropDownButtonIcon(height);

    const int x = comboBox_->x() + comboBox_->width() - dropDownWidth;
    dropDownButton_->move(x, comboBox_->y());
    dropDownButton_->raise();
}

void QelSelect::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (dropDownButton_ == nullptr) {
        return;
    }

    const int x = comboBox_->x() + comboBox_->width() - dropDownButton_->width();
    dropDownButton_->move(x, comboBox_->y());
    dropDownButton_->raise();
}

void QelSelect::updateDropDownButtonIcon(int buttonHeight)
{
    const int iconSize = qMax(8, buttonHeight / 3);
    const QColor iconColor = isEnabled() ? QColor("#909399") : QColor("#C0C4CC");
    dropDownButton_->setIcon(QelIcon(QelIcon::ChevronDown, iconSize, iconColor));
    dropDownButton_->setIconSize(QSize(iconSize, iconSize));
}

} // namespace qel
