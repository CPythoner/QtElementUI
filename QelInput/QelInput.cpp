#include "QelInput.h"

#include <QHBoxLayout>

namespace qel {

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
    lineEdit_->setStyleSheet(QString(
        "QLineEdit {"
        " border: 1px solid #DCDFE6;"
        " border-radius: 4px;"
        " color: #606266;"
        " padding-left: %1px;"
        " padding-right: %1px;"
        " font-size: %2px;"
        "}"
        "QLineEdit:focus {"
        " border: 1px solid #409EFF;"
        "}"
        "QLineEdit:disabled {"
        " color: #C0C4CC;"
        " background: #F5F7FA;"
        " border: 1px solid #E4E7ED;"
        "}"
    ).arg(horizontalPadding).arg(fontSize));
}

void QelInput::updatePasswordAction()
{
    if (passwordAction_ != nullptr) {
        lineEdit_->removeAction(passwordAction_);
        delete passwordAction_;
        passwordAction_ = nullptr;
    }

    if (type_ == Type::Password && showPassword_) {
        passwordAction_ = lineEdit_->addAction(passwordVisible_ ? "Hide" : "Show", QLineEdit::TrailingPosition);
        connect(passwordAction_, &QAction::triggered, this, &QelInput::onTogglePasswordVisibility);
    }
}

} // namespace qel
