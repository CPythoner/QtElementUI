#ifndef QELSWITCH_H
#define QELSWITCH_H

#include <QPropertyAnimation>
#include <QWidget>

namespace qel {

class QelSwitch : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal offset READ offset WRITE setOffset)

public:
    enum class Size {
        Large,
        Default,
        Small
    };

    explicit QelSwitch(QWidget *parent = nullptr);

    bool checked() const;
    void setChecked(bool checked);
    void setDisabled(bool disabled);
    void setSize(Size size);

    qreal offset() const;
    void setOffset(qreal offset);

signals:
    void toggled(bool checked);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void applySize();
    void syncOffset(bool animated);

private:
    bool checked_ = false;
    qreal offset_ = 0.0;
    Size size_ = Size::Default;
    QPropertyAnimation *animation_ = nullptr;
    int controlWidth_ = 40;
    int controlHeight_ = 20;
    int knobDiameter_ = 16;
};

} // namespace qel

#endif // QELSWITCH_H
