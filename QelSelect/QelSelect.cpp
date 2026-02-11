#include "QelSelect.h"

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

    switch (size_) {
    case Size::Large:
        height = 40;
        fontSize = 14;
        horizontalPadding = 14;
        break;
    case Size::Default:
        height = 32;
        fontSize = 14;
        horizontalPadding = 12;
        break;
    case Size::Small:
        height = 24;
        fontSize = 12;
        horizontalPadding = 8;
        break;
    }

    comboBox_->setFixedHeight(height);
    comboBox_->setStyleSheet(QString(
        "QComboBox {"
        " border: 1px solid #DCDFE6;"
        " border-radius: 4px;"
        " color: #606266;"
        " padding-left: %1px;"
        " padding-right: %1px;"
        " font-size: %2px;"
        "}"
        "QComboBox:focus {"
        " border: 1px solid #409EFF;"
        "}"
        "QComboBox:disabled {"
        " color: #C0C4CC;"
        " background: #F5F7FA;"
        " border: 1px solid #E4E7ED;"
        "}"
        "QComboBox QAbstractItemView {"
        " border: 1px solid #E4E7ED;"
        " selection-background-color: #ECF5FF;"
        "}"
    ).arg(horizontalPadding).arg(fontSize));
}

} // namespace qel
