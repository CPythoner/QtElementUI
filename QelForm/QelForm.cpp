#include "QelForm.h"

namespace qel {

namespace {

const char *kRegularTextColor = "#606266";
const char *kDangerColor = "#F56C6C";

} // namespace

QelFormItem::QelFormItem(const QString &label, QWidget *parent)
    : QWidget(parent)
    , label_(label)
{
    labelWidget_ = new QLabel(this);
    errorWidget_ = new QLabel(this);
    fieldContainer_ = new QWidget(this);
    fieldLayout_ = new QVBoxLayout(fieldContainer_);
    layout_ = new QGridLayout(this);

    fieldLayout_->setContentsMargins(0, 0, 0, 0);
    fieldLayout_->setSpacing(0);

    layout_->setContentsMargins(0, 0, 0, 0);
    layout_->setHorizontalSpacing(12);
    layout_->setVerticalSpacing(4);

    labelWidget_->setStyleSheet(
        QString("color: %1; font-size: 14px;").arg(kRegularTextColor));

    errorWidget_->setStyleSheet(
        QString("color: %1; font-size: 12px;").arg(kDangerColor));
    errorWidget_->setWordWrap(true);
    errorWidget_->hide();

    updateLabelText();
    rebuildLayout();
}

void QelFormItem::setLabel(const QString &label)
{
    label_ = label;
    updateLabelText();
}

QString QelFormItem::label() const
{
    return label_;
}

void QelFormItem::setField(QWidget *field)
{
    if (field_ == field) {
        return;
    }

    if (field_) {
        fieldLayout_->removeWidget(field_);
    }

    field_ = field;
    if (field_) {
        field_->setParent(fieldContainer_);
        fieldLayout_->addWidget(field_);
    }
}

QWidget *QelFormItem::field() const
{
    return field_;
}

void QelFormItem::setValueGetter(const ValueGetter &getter)
{
    valueGetter_ = getter;
}

void QelFormItem::setResetHandler(const ResetHandler &handler)
{
    resetHandler_ = handler;
}

void QelFormItem::setRules(const QList<QelFormRule> &rules)
{
    rules_ = rules;
    rulesRequired_ = false;

    for (const QelFormRule &rule : rules_) {
        if (rule.required) {
            rulesRequired_ = true;
            break;
        }
    }

    updateLabelText();
}

QList<QelFormRule> QelFormItem::rules() const
{
    return rules_;
}

void QelFormItem::setRequired(bool required)
{
    explicitlyRequired_ = required;
    updateLabelText();
}

bool QelFormItem::isRequired() const
{
    return explicitlyRequired_ || rulesRequired_;
}

void QelFormItem::setLabelPosition(LabelPosition position)
{
    if (labelPosition_ == position) {
        return;
    }

    labelPosition_ = position;
    rebuildLayout();
}

QelFormItem::LabelPosition QelFormItem::labelPosition() const
{
    return labelPosition_;
}

void QelFormItem::setLabelWidth(int width)
{
    labelWidth_ = qMax(0, width);
    rebuildLayout();
}

int QelFormItem::labelWidth() const
{
    return labelWidth_;
}

bool QelFormItem::validate()
{
    const bool needsValue = isRequired() || !rules_.isEmpty();
    if (needsValue && !valueGetter_) {
        const QString message = "Validation value getter is not configured.";
        setError(message);
        emit validationChanged(false, message);
        return false;
    }

    const QString value = valueGetter_ ? valueGetter_() : QString();

    if (isRequired() && value.trimmed().isEmpty()) {
        QString message;
        for (const QelFormRule &rule : rules_) {
            if (rule.required && !rule.message.isEmpty()) {
                message = rule.message;
                break;
            }
        }

        if (message.isEmpty()) {
            message = QString("%1 is required.")
                          .arg(label_.isEmpty() ? QString("This field") : label_);
        }

        setError(message);
        emit validationChanged(false, message);
        return false;
    }

    for (const QelFormRule &rule : rules_) {
        if (rule.minLength >= 0 && value.length() < rule.minLength) {
            const QString message = rule.message.isEmpty()
                ? defaultValidationMessage(rule)
                : rule.message;
            setError(message);
            emit validationChanged(false, message);
            return false;
        }

        if (rule.maxLength >= 0 && value.length() > rule.maxLength) {
            const QString message = rule.message.isEmpty()
                ? defaultValidationMessage(rule)
                : rule.message;
            setError(message);
            emit validationChanged(false, message);
            return false;
        }

        if (rule.pattern.isValid()
            && !rule.pattern.pattern().isEmpty()
            && !rule.pattern.match(value).hasMatch()) {
            const QString message = rule.message.isEmpty()
                ? defaultValidationMessage(rule)
                : rule.message;
            setError(message);
            emit validationChanged(false, message);
            return false;
        }

        if (rule.validator) {
            QString customMessage;
            if (!rule.validator(value, customMessage)) {
                const QString message = !customMessage.isEmpty()
                    ? customMessage
                    : (!rule.message.isEmpty()
                           ? rule.message
                           : defaultValidationMessage(rule));
                setError(message);
                emit validationChanged(false, message);
                return false;
            }
        }
    }

    clearValidate();
    emit validationChanged(true, QString());
    return true;
}

void QelFormItem::resetField()
{
    if (resetHandler_) {
        resetHandler_();
    }
    clearValidate();
}

void QelFormItem::setError(const QString &message)
{
    errorWidget_->setText(message);
    errorWidget_->setVisible(!message.isEmpty());
}

void QelFormItem::clearValidate()
{
    errorWidget_->clear();
    errorWidget_->hide();
}

void QelFormItem::rebuildLayout()
{
    layout_->removeWidget(labelWidget_);
    layout_->removeWidget(fieldContainer_);
    layout_->removeWidget(errorWidget_);

    if (labelPosition_ == LabelPosition::Top) {
        labelWidget_->setMinimumWidth(0);
        labelWidget_->setMaximumWidth(QWIDGETSIZE_MAX);
        labelWidget_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        layout_->addWidget(labelWidget_, 0, 0, 1, 2);
        layout_->addWidget(fieldContainer_, 1, 0, 1, 2);
        layout_->addWidget(errorWidget_, 2, 0, 1, 2);
    } else {
        labelWidget_->setFixedWidth(labelWidth_);
        labelWidget_->setAlignment(
            (labelPosition_ == LabelPosition::Right
                 ? Qt::AlignRight
                 : Qt::AlignLeft)
            | Qt::AlignVCenter);

        layout_->addWidget(labelWidget_, 0, 0);
        layout_->addWidget(fieldContainer_, 0, 1);
        layout_->addWidget(errorWidget_, 1, 1);
    }

    layout_->setColumnStretch(1, 1);
}

void QelFormItem::updateLabelText()
{
    const QString escapedLabel = label_.toHtmlEscaped();
    if (isRequired()) {
        labelWidget_->setText(
            QString("<span style=\"color:%1\">*</span> %2")
                .arg(kDangerColor, escapedLabel));
    } else {
        labelWidget_->setText(escapedLabel);
    }
}

QString QelFormItem::defaultValidationMessage(const QelFormRule &rule) const
{
    const QString fieldName = label_.isEmpty() ? QString("This field") : label_;

    if (rule.minLength >= 0 && rule.maxLength >= 0) {
        return QString("%1 length must be between %2 and %3.")
            .arg(fieldName)
            .arg(rule.minLength)
            .arg(rule.maxLength);
    }

    if (rule.minLength >= 0) {
        return QString("%1 must contain at least %2 characters.")
            .arg(fieldName)
            .arg(rule.minLength);
    }

    if (rule.maxLength >= 0) {
        return QString("%1 must contain at most %2 characters.")
            .arg(fieldName)
            .arg(rule.maxLength);
    }

    if (rule.pattern.isValid() && !rule.pattern.pattern().isEmpty()) {
        return QString("%1 format is invalid.").arg(fieldName);
    }

    return QString("%1 is invalid.").arg(fieldName);
}

QelForm::QelForm(QWidget *parent)
    : QWidget(parent)
{
    layout_ = new QVBoxLayout(this);
    layout_->setContentsMargins(0, 0, 0, 0);
    layout_->setSpacing(18);
    layout_->addStretch();
}

void QelForm::addItem(QelFormItem *item)
{
    if (!item || items_.contains(item)) {
        return;
    }

    item->setParent(this);
    item->setLabelPosition(labelPosition_);
    item->setLabelWidth(labelWidth_);

    layout_->insertWidget(layout_->count() - 1, item);
    items_.append(item);
}

QList<QelFormItem *> QelForm::items() const
{
    return items_;
}

bool QelForm::validate()
{
    bool valid = true;
    for (QelFormItem *item : items_) {
        valid = item->validate() && valid;
    }

    emit validationFinished(valid);
    return valid;
}

bool QelForm::validateField(QelFormItem *item)
{
    if (!item || !items_.contains(item)) {
        return false;
    }

    return item->validate();
}

void QelForm::clearValidate()
{
    for (QelFormItem *item : items_) {
        item->clearValidate();
    }
}

void QelForm::resetFields()
{
    for (QelFormItem *item : items_) {
        item->resetField();
    }
}

void QelForm::setLabelPosition(QelFormItem::LabelPosition position)
{
    labelPosition_ = position;
    for (QelFormItem *item : items_) {
        item->setLabelPosition(position);
    }
}

void QelForm::setLabelWidth(int width)
{
    labelWidth_ = qMax(0, width);
    for (QelFormItem *item : items_) {
        item->setLabelWidth(labelWidth_);
    }
}

} // namespace qel
