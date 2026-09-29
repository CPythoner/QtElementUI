#ifndef QELFORM_H
#define QELFORM_H

#include "QelFormRule.h"

#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QVBoxLayout>
#include <QWidget>

#include <functional>

namespace qel {

class QelFormItem : public QWidget
{
    Q_OBJECT

public:
    enum class LabelPosition {
        Left,
        Right,
        Top
    };

    using ValueGetter = std::function<QString()>;
    using ResetHandler = std::function<void()>;

    explicit QelFormItem(const QString &label = QString(), QWidget *parent = nullptr);

    void setLabel(const QString &label);
    QString label() const;

    void setField(QWidget *field);
    QWidget *field() const;

    void setValueGetter(const ValueGetter &getter);
    void setResetHandler(const ResetHandler &handler);

    void setRules(const QList<QelFormRule> &rules);
    QList<QelFormRule> rules() const;

    void setRequired(bool required);
    bool isRequired() const;

    void setLabelPosition(LabelPosition position);
    LabelPosition labelPosition() const;

    void setLabelWidth(int width);
    int labelWidth() const;

    bool validate();
    void resetField();
    void setError(const QString &message);
    void clearValidate();

signals:
    void validationChanged(bool valid, const QString &message);

private:
    void rebuildLayout();
    void updateLabelText();
    QString defaultValidationMessage(const QelFormRule &rule) const;

private:
    QString label_;
    QWidget *field_ = nullptr;
    QWidget *fieldContainer_ = nullptr;
    QVBoxLayout *fieldLayout_ = nullptr;
    QLabel *labelWidget_ = nullptr;
    QLabel *errorWidget_ = nullptr;
    QGridLayout *layout_ = nullptr;

    ValueGetter valueGetter_;
    ResetHandler resetHandler_;
    QList<QelFormRule> rules_;

    LabelPosition labelPosition_ = LabelPosition::Right;
    int labelWidth_ = 100;
    bool explicitlyRequired_ = false;
    bool rulesRequired_ = false;
};

class QelForm : public QWidget
{
    Q_OBJECT

public:
    explicit QelForm(QWidget *parent = nullptr);

    void addItem(QelFormItem *item);
    QList<QelFormItem *> items() const;

    bool validate();
    bool validateField(QelFormItem *item);
    void clearValidate();
    void resetFields();

    void setLabelPosition(QelFormItem::LabelPosition position);
    void setLabelWidth(int width);

signals:
    void validationFinished(bool valid);

private:
    QVBoxLayout *layout_ = nullptr;
    QList<QelFormItem *> items_;
    QelFormItem::LabelPosition labelPosition_ = QelFormItem::LabelPosition::Right;
    int labelWidth_ = 100;
};

} // namespace qel

#endif // QELFORM_H
