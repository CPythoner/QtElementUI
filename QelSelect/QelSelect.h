#ifndef QELSELECT_H
#define QELSELECT_H

#include <QtWidgets/QComboBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QMouseEvent>
#include <cstdint>

class QelSelect : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(QString placeholder READ placeholder WRITE setPlaceholder)
    Q_PROPERTY(bool clearable READ clearable WRITE setClearable)
    Q_PROPERTY(bool disabled READ isDisabled WRITE setDisabled)
    Q_PROPERTY(bool filterable READ filterable WRITE setFilterable)

public:
    explicit QelSelect(QWidget* parent = nullptr);

    QString placeholder() const;
    void    setPlaceholder(const QString& placeholder);

    bool clearable() const;
    void setClearable(bool clearable);

    bool isDisabled() const;
    void setDisabled(bool disabled);

    bool filterable() const;
    void setFilterable(bool filterable);

protected:
    void paintEvent(QPaintEvent* event) override;
    void focusInEvent(QFocusEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    void handleActivated(int index);

private:
    void initUI();
    void setupStyle();

    QString    m_placeholder;
    bool       m_clearable;
    bool       m_disabled;
    bool       m_filterable;
    QLineEdit* m_lineEdit;
};

#endif  // QELSELECT_H
