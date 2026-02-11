#include "QelAnimationHelper.h"

#include <QAbstractAnimation>
#include <QGraphicsOpacityEffect>
#include <QPointer>
#include <QPropertyAnimation>
#include <QWidget>

namespace qel {

bool QelAnimationHelper::animationEnabled_ = true;

void QelAnimationHelper::setAnimationEnabled(bool enabled)
{
    animationEnabled_ = enabled;
}

bool QelAnimationHelper::isAnimationEnabled()
{
    return animationEnabled_;
}

void QelAnimationHelper::fadeIn(QWidget *target, int duration)
{
    if (target == nullptr) {
        return;
    }

    target->show();

    if (!animationEnabled_) {
        target->setWindowOpacity(1.0);
        return;
    }

    auto *effect = qobject_cast<QGraphicsOpacityEffect *>(target->graphicsEffect());
    if (effect == nullptr) {
        effect = new QGraphicsOpacityEffect(target);
        target->setGraphicsEffect(effect);
    }

    auto *animation = new QPropertyAnimation(effect, "opacity", target);
    animation->setDuration(duration);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void QelAnimationHelper::fadeOut(QWidget *target, int duration)
{
    if (target == nullptr) {
        return;
    }

    if (!animationEnabled_) {
        target->hide();
        return;
    }

    auto *effect = qobject_cast<QGraphicsOpacityEffect *>(target->graphicsEffect());
    if (effect == nullptr) {
        effect = new QGraphicsOpacityEffect(target);
        target->setGraphicsEffect(effect);
    }

    auto *animation = new QPropertyAnimation(effect, "opacity", target);
    animation->setDuration(duration);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    QPointer<QWidget> safeTarget(target);
    QObject::connect(animation, &QPropertyAnimation::finished, target, [safeTarget]() {
        if (safeTarget != nullptr) {
            safeTarget->hide();
        }
    });

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void QelAnimationHelper::pressFeedback(QWidget *target, int duration)
{
    if (target == nullptr) {
        return;
    }

    if (!animationEnabled_) {
        return;
    }

    const QRect baseGeometry = target->geometry();
    const int offsetX = baseGeometry.width() > 8 ? 1 : 0;
    const int offsetY = baseGeometry.height() > 8 ? 1 : 0;
    const QRect pressedGeometry = baseGeometry.adjusted(offsetX, offsetY, -offsetX, -offsetY);

    auto *animation = new QPropertyAnimation(target, "geometry", target);
    animation->setDuration(duration);
    animation->setKeyValueAt(0.0, baseGeometry);
    animation->setKeyValueAt(0.5, pressedGeometry);
    animation->setKeyValueAt(1.0, baseGeometry);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void QelAnimationHelper::focusRingPulse(QWidget *target, int duration, QEasingCurve::Type easing)
{
    if (target == nullptr) {
        return;
    }

    if (!animationEnabled_) {
        return;
    }

    auto *animation = new QPropertyAnimation(target, "windowOpacity", target);
    animation->setDuration(duration);
    animation->setKeyValueAt(0.0, 1.0);
    animation->setKeyValueAt(0.5, 0.92);
    animation->setKeyValueAt(1.0, 1.0);
    animation->setEasingCurve(easing);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

} // namespace qel
