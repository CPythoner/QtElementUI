#ifndef QELSELECT_H
#define QELSELECT_H

#include <QComboBox>
#include <QStringList>
#include <QResizeEvent>
#include <QToolButton>
#include <QVariant>
#include <QWidget>

namespace qel {

class QelSelect : public QWidget
{
    Q_OBJECT

public:
    enum class Size {
        Large,
        Default,
        Small
    };

    explicit QelSelect(QWidget *parent = nullptr);

    void setOptions(const QStringList &options);
    void addOption(const QString &label, const QVariant &value = QVariant());
    void clearOptions();

    void setCurrentValue(const QVariant &value);
    QVariant currentValue() const;
    QString currentText() const;

    void setPlaceholder(const QString &placeholder);
    void setDisabled(bool disabled);
    void setSize(Size size);

signals:
    void currentIndexChanged(int index);
    void currentTextChanged(const QString &text);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void applyStyle();
    void updateDropDownButtonIcon(int buttonHeight);

private:
    QComboBox *comboBox_ = nullptr;
    QToolButton *dropDownButton_ = nullptr;
    Size size_ = Size::Default;
};

} // namespace qel

#endif // QELSELECT_H
