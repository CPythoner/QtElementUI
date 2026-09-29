#include "QelInput.h"

#include "../QelStyleHelper/QelStyleHelper.h"
#include "../QelTheme/QelTheme.h"

#include <QHBoxLayout>

namespace qel {

namespace {

QelStyleHelper::StateStyleSet inputStateStyles()
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

QelInput::QelInput(QWidget *parent,
                   Type type,
                   const QString &placeholder,
                   const QString &value)
    : QWidget(parent),
      lineEdit_(new QLineEdit(this)),
      type_(type)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(lineEdit_);

    lineEdit_->setPlaceholderText(placeholder);
    lineEdit_->setText(value);

    connect(lineEdit_, &QLineEdit::textChanged, this, &QelInput::textChanged);

    setType(type_);
    setClearable(false);
    applyStyle();
}

void QelInput::setType(Type type)
{
    type_ = type;

    if (type_ == Type::Password) {
        lineEdit_->setEchoMode(passwordVisible_ ? QLineEdit::Normal : QLineEdit::Password);
    } else {
        lineEdit_->setEchoMode(QLineEdit::Normal);
        passwordVisible_ = false;
    }

    updatePasswordAction();
}

void QelInput::setSize(Size size)
{
    size_ = size;
    applyStyle();
}

void QelInput::setClearable(bool clearable)
{
    clearable_ = clearable;
    lineEdit_->setClearButtonEnabled(clearable_);
}

void QelInput::setShowPassword(bool enable)
{
    showPassword_ = enable;
    updatePasswordAction();
}

void QelInput::setPlaceholder(const QString &placeholder)
{
    lineEdit_->setPlaceholderText(placeholder);
}

void QelInput::setDisabled(bool disabled)
{
    lineEdit_->setDisabled(disabled);
}

void QelInput::setReadonly(bool readonly)
{
    lineEdit_->setReadOnly(readonly);
}

void QelInput::setText(const QString &value)
{
    lineEdit_->setText(value);
}

QString QelInput::text() const
{
    return lineEdit_->text();
}

void QelInput::onTogglePasswordVisibility()
{
    if (type_ != Type::Password) {
        return;
    }

    passwordVisible_ = !passwordVisible_;
    lineEdit_->setEchoMode(passwordVisible_ ? QLineEdit::Normal : QLineEdit::Password);

    if (passwordAction_ != nullptr) {
        passwordAction_->setText(passwordVisible_ ? "Hide" : "Show");
    }
}

void QelInput::applyStyle()
{
    int height = 40;
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

    lineEdit_->setFixedHeight(height);

    QString style = QelStyleHelper::composeStateStyleSheet(
        "QLineEdit",
        QString(),
        inputStateStyles(),
        true);

    style += QString(
        "QLineEdit {"
        " border-radius: 4px;"
        " padding-left: %1px;"
        " padding-right: %1px;"
        " font-size: %2px;"
        "}"
    ).arg(horizontalPadding).arg(fontSize);

    lineEdit_->setStyleSheet(style);
}

void QelInput::updatePasswordAction()
{
    if (passwordAction_ != nullptr) {
        lineEdit_->removeAction(passwordAction_);
        delete passwordAction_;
        passwordAction_ = nullptr;
    }

    if (type_ == Type::Password && showPassword_) {
        passwordAction_ = lineEdit_->addAction(
            passwordVisible_ ? "Hide" : "Show",
            QLineEdit::TrailingPosition);
        connect(
            passwordAction_,
            &QAction::triggered,
            this,
            &QelInput::onTogglePasswordVisibility);
    }
}

} // namespace qel
