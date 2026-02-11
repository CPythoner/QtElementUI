#ifndef QELINPUT_H
#define QELINPUT_H

#include <QAction>
#include <QLineEdit>
#include <QWidget>

namespace qel {

class QelInput : public QWidget
{
    Q_OBJECT

public:
    enum class Type {
        Text,
        Password
    };

    enum class Size {
        Large,
        Default,
        Small
    };

    explicit QelInput(QWidget *parent = nullptr,
                      Type type = Type::Text,
                      const QString &placeholder = QString(),
                      const QString &value = QString());

    void setType(Type type);
    void setSize(Size size);
    void setClearable(bool clearable);
    void setShowPassword(bool enable);
    void setPlaceholder(const QString &placeholder);
    void setDisabled(bool disabled);
    void setReadonly(bool readonly);
    void setText(const QString &value);

    QString text() const;

signals:
    void textChanged(const QString &value);

private slots:
    void onTogglePasswordVisibility();

private:
    void applyStyle();
    void updatePasswordAction();

private:
    QLineEdit *lineEdit_ = nullptr;
    QAction *passwordAction_ = nullptr;
    Type type_ = Type::Text;
    Size size_ = Size::Default;
    bool clearable_ = false;
    bool showPassword_ = false;
    bool passwordVisible_ = false;
};

} // namespace qel

#endif // QELINPUT_H
