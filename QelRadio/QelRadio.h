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

    enum class StyleType {
        Default,
        Button
    };

    explicit QelRadio(const QString &text = QString(), QWidget *parent = nullptr);

    explicit QelRadio(const QString &text,
                      bool checked,
                      bool disabled,
                      bool border,
                      Size size,
                      StyleType styleType = StyleType::Default,
                      QWidget *parent = nullptr);

    void setSize(Size size);
    void setBorder(bool border);
    void setStyleType(StyleType styleType);

    Size size() const { return size_; }
    bool border() const { return border_; }
    StyleType styleType() const { return styleType_; }

private:
    void applyStyle();

private:
    Size size_ = Size::Default;
    bool border_ = false;
    StyleType styleType_ = StyleType::Default;
};

} // namespace qel

#endif // QELRADIO_H
