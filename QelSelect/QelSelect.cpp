#include "QelSelect.h"

#include "../QelIcon/QelIcon.h"
#include "../QelStyleHelper/QelStyleHelper.h"
#include "../QelTheme/QelTheme.h"

#include <QAbstractItemView>
#include <QHBoxLayout>
#include <QLineEdit>

namespace qel {

namespace {

QelStyleHelper::StateStyleSet selectStateStyles()
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

QelStyleHelper::StateStyleSet dropDownButtonStateStyles()
{
    const QelTheme::ColorTokens &c = QelTheme::colors();

    return {
        {c.fillLight, c.textSecondary, c.borderBase},
        {c.primaryLight, c.primary, c.primary},
        {c.primaryLight, c.primary, c.primary},
        {c.primaryLight, c.primary, c.primary},
        {c.fillLight, c.textPlaceholder, c.borderLight},
        {c.fillLight, c.textPlaceholder, c.borderLight}
    };
}

} // namespace

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
    if (!value.isValid() || value.toString().isEmpty()) {
        comboBox_->setCurrentIndex(-1);
        return;
    }

    int index = comboBox_->findData(value);
    if (index < 0) {
        index = comboBox_->findText(value.toString());
    }

    comboBox_->setCurrentIndex(index);
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
    comboBox_->setCurrentIndex(-1);
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

    const QelTheme::ColorTokens &c = QelTheme::colors();

    QFont font = comboBox_->font();
    font.setPointSize(fontSize);
    comboBox_->setFont(font);
    if (comboBox_->view()) {
        comboBox_->view()->setFont(font);
        comboBox_->view()->setWindowFlag(Qt::NoDropShadowWindowHint, true);
        if (comboBox_->view()->window()) {
            comboBox_->view()->window()->setAttribute(Qt::WA_TranslucentBackground, false);
            comboBox_->view()->window()->setWindowOpacity(1.0);
        }
    }

    comboBox_->setFixedHeight(height);

    QString comboStyle = QelStyleHelper::composeStateStyleSheet(
        "QComboBox",
        QString(),
        selectStateStyles(),
        true);

    comboStyle += QString(
        "QComboBox {"
        " border-radius: 4px;"
        " padding-left: %1px;"
        " padding-right: %2px;"
        "}"
        "QComboBox::drop-down {"
        " width: 0px;"
        " border: 0px;"
        "}"
        "QComboBox::down-arrow {"
        " image: none;"
        "}"
        "QComboBox QAbstractItemView {"
        " border: 1px solid %3;"
        " background-color: %4;"
        " color: %5;"
        " selection-background-color: %6;"
        " selection-color: %7;"
        " outline: 0;"
        "}"
    )
        .arg(horizontalPadding)
        .arg(dropDownWidth)
        .arg(c.borderLight)
        .arg(c.fillBlank)
        .arg(c.textRegular)
        .arg(c.primaryLight)
        .arg(c.primary);

    comboBox_->setStyleSheet(comboStyle);

    dropDownButton_->setFixedSize(dropDownWidth, height);

    QString buttonStyle = QelStyleHelper::composeStateStyleSheet(
        "QToolButton",
        QString(),
        dropDownButtonStateStyles(),
        true);

    buttonStyle +=
        "QToolButton {"
        " border-left: 0px;"
        " border-top-right-radius: 4px;"
        " border-bottom-right-radius: 4px;"
        "}";

    dropDownButton_->setStyleSheet(buttonStyle);

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
    const QelTheme::ColorTokens &c = QelTheme::colors();
    const int iconSize = qMax(8, buttonHeight / 3);
    const QColor iconColor = dropDownButton_->isEnabled()
        ? QColor(c.textSecondary)
        : QColor(c.textPlaceholder);

    dropDownButton_->setIcon(QelIcon(QelIcon::ChevronDown, iconSize, iconColor));
    dropDownButton_->setIconSize(QSize(iconSize, iconSize));
}

} // namespace qel
