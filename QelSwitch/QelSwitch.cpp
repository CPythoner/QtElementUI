#include "QelSwitch.h"

#include <QMouseEvent>
#include <QPainter>

namespace qel {

QelSwitch::QelSwitch(QWidget *parent)
    : QWidget(parent),
      animation_(new QPropertyAnimation(this, "offset", this))
{
    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::StrongFocus);

    animation_->setDuration(150);

    applySize();
    syncOffset(false);
}

bool QelSwitch::checked() const
{
    return checked_;
}

void QelSwitch::setChecked(bool checked)
{
    if (checked_ == checked) {
        return;
    }

    checked_ = checked;
    syncOffset(true);
    update();
    emit toggled(checked_);
}

void QelSwitch::setDisabled(bool disabled)
{
    setEnabled(!disabled);
    update();
}

void QelSwitch::setSize(Size size)
{
    size_ = size;
    applySize();
    syncOffset(false);
    update();
}

qreal QelSwitch::offset() const
{
    return offset_;
}

void QelSwitch::setOffset(qreal offset)
{
    offset_ = offset;
    update();
}

void QelSwitch::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    if (!isEnabled() || event->button() != Qt::LeftButton) {
        return;
    }

    setChecked(!checked_);
}

void QelSwitch::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const QColor activeColor = isEnabled() ? QColor("#409EFF") : QColor("#A0CFFF");
    const QColor inactiveColor = isEnabled() ? QColor("#DCDFE6") : QColor("#E4E7ED");

    QColor bgColor = checked_ ? activeColor : inactiveColor;
    if (underMouse() && isEnabled()) {
        bgColor = checked_ ? QColor("#66B1FF") : QColor("#C0C4CC");
    }

    QRectF trackRect(0, 0, controlWidth_, controlHeight_);
    painter.setPen(Qt::NoPen);
    painter.setBrush(bgColor);
    painter.drawRoundedRect(trackRect, controlHeight_ / 2.0, controlHeight_ / 2.0);

    const qreal top = (controlHeight_ - knobDiameter_) / 2.0;
    QRectF knobRect(offset_, top, knobDiameter_, knobDiameter_);
    painter.setBrush(Qt::white);
    painter.drawEllipse(knobRect);
}

void QelSwitch::applySize()
{
    switch (size_) {
    case Size::Large:
        controlWidth_ = 50;
        controlHeight_ = 24;
        knobDiameter_ = 20;
        break;
    case Size::Default:
        controlWidth_ = 40;
        controlHeight_ = 20;
        knobDiameter_ = 16;
        break;
    case Size::Small:
        controlWidth_ = 32;
        controlHeight_ = 16;
        knobDiameter_ = 12;
        break;
    }

    setFixedSize(controlWidth_, controlHeight_);
}

void QelSwitch::syncOffset(bool animated)
{
    const qreal minX = 2.0;
    const qreal maxX = controlWidth_ - knobDiameter_ - 2.0;
    const qreal target = checked_ ? maxX : minX;

    if (!animated) {
        animation_->stop();
        offset_ = target;
        return;
    }

    animation_->stop();
    animation_->setStartValue(offset_);
    animation_->setEndValue(target);
    animation_->start();
}

} // namespace qel
