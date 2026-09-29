#include "QelSwitch.h"

#include "../QelStyleHelper/QelStyleHelper.h"
#include "../QelTheme/QelTheme.h"

#include <QMouseEvent>
#include <QPainter>

namespace qel {

namespace {

QelStyleHelper::StateStyleSet checkedTrackStyles()
{
    const QelTheme::ColorTokens &c = QelTheme::colors();

    return {
        {c.primary, c.fillBlank, c.primary},
        {c.primaryHover, c.fillBlank, c.primaryHover},
        {c.primaryHover, c.fillBlank, c.primaryHover},
        {c.primaryHover, c.fillBlank, c.primary},
        {c.primaryDisabled, c.fillBlank, c.primaryDisabled},
        {c.primaryDisabled, c.fillBlank, c.primaryDisabled}
    };
}

QelStyleHelper::StateStyleSet uncheckedTrackStyles()
{
    const QelTheme::ColorTokens &c = QelTheme::colors();

    return {
        {c.borderBase, c.fillBlank, c.borderBase},
        {c.textPlaceholder, c.fillBlank, c.textPlaceholder},
        {c.textPlaceholder, c.fillBlank, c.textPlaceholder},
        {c.textPlaceholder, c.fillBlank, c.primary},
        {c.borderLight, c.fillBlank, c.borderLight},
        {c.borderLight, c.fillBlank, c.borderLight}
    };
}

} // namespace

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

    QelStateContext context;
    context.enabled = isEnabled();
    context.hovered = underMouse();
    context.focused = hasFocus();

    const QelVisualState state = QelStyleHelper::resolveState(context);
    const QelStyleHelper::StateStyleSet styles =
        checked_ ? checkedTrackStyles() : uncheckedTrackStyles();
    const QelStyleHelper::ComponentStyle visual =
        QelStyleHelper::styleForState(styles, state);

    const QelTheme::ColorTokens &c = QelTheme::colors();

    QRectF trackRect(0.5, 0.5, controlWidth_ - 1.0, controlHeight_ - 1.0);
    if (hasFocus() && isEnabled()) {
        painter.setPen(QPen(QColor(c.primary), 1.0));
    } else {
        painter.setPen(Qt::NoPen);
    }

    painter.setBrush(QColor(visual.background));
    painter.drawRoundedRect(trackRect, controlHeight_ / 2.0, controlHeight_ / 2.0);

    const qreal top = (controlHeight_ - knobDiameter_) / 2.0;
    const QRectF knobRect(offset_, top, knobDiameter_, knobDiameter_);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(c.fillBlank));
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
