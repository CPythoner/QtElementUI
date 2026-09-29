#ifndef QELFORMTESTER_H
#define QELFORMTESTER_H

#include "QelForm.h"

#include "../QelButton/QelButton.h"
#include "../QelInput/QelInput.h"
#include "../QelSelect/QelSelect.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>

using qel::QelButton;
using qel::QelForm;
using qel::QelFormItem;
using qel::QelFormRule;
using qel::QelInput;
using qel::QelSelect;

class QelFormTester : public QWidget
{
public:
    explicit QelFormTester(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        QVBoxLayout *pageLayout = new QVBoxLayout(this);
        pageLayout->setSpacing(16);

        QLabel *title = new QLabel("Form", this);
        title->setStyleSheet(
            "font-size: 28px; font-weight: 700; color: #303133;");
        pageLayout->addWidget(title);

        QLabel *description = new QLabel(
            "Element-style form layout, validation and reset behavior.", this);
        description->setStyleSheet("font-size: 14px; color: #606266;");
        pageLayout->addWidget(description);

        form_ = new QelForm(this);
        form_->setLabelWidth(110);

        nameInput_ = new QelInput(
            nullptr, QelInput::Type::Text, "Enter name");
        nameInput_->setClearable(true);

        QelFormItem *nameItem = new QelFormItem("Name");
        nameItem->setField(nameInput_);
        nameItem->setValueGetter([this]() { return nameInput_->text(); });
        nameItem->setResetHandler(
            [this]() { nameInput_->setText(QString()); });
        nameItem->setRules({
            QelFormRule::requiredRule("Please enter a name."),
            QelFormRule::lengthRule(
                2, 20, "Name must contain 2 to 20 characters.")
        });
        form_->addItem(nameItem);

        emailInput_ = new QelInput(
            nullptr, QelInput::Type::Text, "name@example.com");
        emailInput_->setClearable(true);

        QelFormItem *emailItem = new QelFormItem("Email");
        emailItem->setField(emailInput_);
        emailItem->setValueGetter([this]() { return emailInput_->text(); });
        emailItem->setResetHandler(
            [this]() { emailInput_->setText(QString()); });
        emailItem->setRules({
            QelFormRule::requiredRule("Please enter an email address."),
            QelFormRule::patternRule(
                QRegularExpression("^[^\\s@]+@[^\\s@]+\\.[^\\s@]+$"),
                "Please enter a valid email address.")
        });
        form_->addItem(emailItem);

        regionSelect_ = new QelSelect();
        regionSelect_->addOption("Singapore", "sg");
        regionSelect_->addOption("China", "cn");
        regionSelect_->addOption("United States", "us");
        regionSelect_->setPlaceholder("Select region");

        QelFormItem *regionItem = new QelFormItem("Region");
        regionItem->setField(regionSelect_);
        regionItem->setValueGetter([this]() {
            return regionSelect_->currentValue().toString();
        });
        regionItem->setResetHandler([this]() {
            regionSelect_->setCurrentValue(QVariant());
        });
        regionItem->setRules({
            QelFormRule::requiredRule("Please select a region.")
        });
        form_->addItem(regionItem);

        pageLayout->addWidget(form_);

        QHBoxLayout *actions = new QHBoxLayout();

        QelButton *validateButton = new QelButton(
            QelButton::Primary,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Validate",
            this);

        QelButton *resetButton = new QelButton(
            QelButton::Default,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Reset",
            this);

        resultLabel_ = new QLabel(this);
        resultLabel_->setStyleSheet("font-size: 13px; color: #606266;");

        connect(validateButton, &QPushButton::clicked, this, [this]() {
            const bool valid = form_->validate();
            resultLabel_->setText(
                valid
                    ? "Validation passed."
                    : "Please fix the highlighted fields.");
            resultLabel_->setStyleSheet(
                valid
                    ? "font-size: 13px; color: #67C23A;"
                    : "font-size: 13px; color: #F56C6C;");
        });

        connect(resetButton, &QPushButton::clicked, this, [this]() {
            form_->resetFields();
            resultLabel_->clear();
        });

        actions->addWidget(validateButton);
        actions->addWidget(resetButton);
        actions->addWidget(resultLabel_);
        actions->addStretch();

        pageLayout->addLayout(actions);
        pageLayout->addStretch();
    }

private:
    QelForm *form_ = nullptr;
    QelInput *nameInput_ = nullptr;
    QelInput *emailInput_ = nullptr;
    QelSelect *regionSelect_ = nullptr;
    QLabel *resultLabel_ = nullptr;
};

#endif // QELFORMTESTER_H
