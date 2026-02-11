#ifndef QELRADIO_H
#define QELRADIO_H

#include <QRadioButton>

namespace qel {

class QelRadio : public QRadioButton
{
    Q_OBJECT

public:
    enum class Size {
        Large,
        Default,
        Small
    };

    explicit QelRadio(const QString &text = QString(), QWidget *parent = nullptr);

    void setSize(Size size);

private:
    void applyStyle();

private:
    Size size_ = Size::Default;
};

} // namespace qel

#endif // QELRADIO_H
