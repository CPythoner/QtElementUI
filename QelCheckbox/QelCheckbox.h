#ifndef QELCHECKBOX_H
#define QELCHECKBOX_H

#include <QCheckBox>

namespace qel {

class QelCheckbox : public QCheckBox
{
    Q_OBJECT

public:
    enum class Size {
        Large,
        Default,
        Small
    };

    explicit QelCheckbox(const QString &text = QString(), QWidget *parent = nullptr);

    explicit QelCheckbox(const QString &text,
                         bool checked = false,
                         bool disabled = false,
                         bool indeterminate = false,
                         bool border = false,
                         Size size = Size::Default,
                         QWidget *parent = nullptr);

    void setSize(Size size);
    void setBorder(bool border);
    void setIndeterminate(bool indeterminate);

    Size size() const { return size_; }
    bool border() const { return border_; }

private:
    void applyStyle();

private:
    Size size_ = Size::Default;
    bool border_ = false;
};

} // namespace qel

#endif // QELCHECKBOX_H
