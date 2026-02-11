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

    void setSize(Size size);
    void setIndeterminate(bool indeterminate);

private:
    void applyStyle();

private:
    Size size_ = Size::Default;
};

} // namespace qel

#endif // QELCHECKBOX_H
