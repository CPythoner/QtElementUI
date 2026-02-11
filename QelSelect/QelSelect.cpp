#include "QelSelect.h"

#include <QAbstractItemView>
#include <QHBoxLayout>
#include <QLineEdit>

namespace qel {

QelSelect::QelSelect(QWidget *parent)
    : QWidget(parent),
      comboBox_(new QComboBox(this))
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(comboBox_);

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
    font.setPointSize(fontSize);
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
        " font-size: %2px;"
        "}"
        "QComboBox:focus {"
        " border: 1px solid #409EFF;"
        "}"
        "QComboBox::drop-down {"
        " subcontrol-origin: padding;"
        " subcontrol-position: top right;"
        " width: %3px;"
        " border-left: 1px solid #DCDFE6;"
        " border-top-right-radius: 4px;"
        " border-bottom-right-radius: 4px;"
        " background-color: #F5F7FA;"
        "}"
        "QComboBox::drop-down:hover {"
        " border-left: 1px solid #409EFF;"
        " background-color: #ECF5FF;"
        "}"
        "QComboBox::down-arrow {"
        " width: 10px;"
        " height: 10px;"
        "}"
        "QComboBox:disabled {"
        " color: #C0C4CC;"
        " background: #F5F7FA;"
        " border: 1px solid #E4E7ED;"
        "}"
        "QComboBox:disabled::drop-down {"
        " border-left: 1px solid #E4E7ED;"
        " background-color: #F5F7FA;"
        "}"
        "QComboBox QAbstractItemView {"
        " border: 1px solid #E4E7ED;"
        " color: #606266;"
        " selection-background-color: #ECF5FF;"
        "}"
    ).arg(horizontalPadding).arg(fontSize).arg(dropDownWidth));
}

} // namespace qel
