#include "QelAnimationHelper.h"

#include <QAbstractAnimation>
#include <QGraphicsOpacityEffect>
#include <QList>
#include <QPointer>
#include <QPropertyAnimation>
#include <QString>
#include <QWidget>

namespace qel {

namespace {

const char *kFadeAnimationObjectName = "qel-fade-animation";

void stopExistingFadeAnimation(QWidget *target)
{
    const QList<QPropertyAnimation *> animations =
        target->findChildren<QPropertyAnimation *>(
            kFadeAnimationObjectName,
            Qt::FindDirectChildrenOnly);

    for (QPropertyAnimation *animation : animations) {
        animation->stop();
        animation->setObjectName(QString());
        animation->deleteLater();
    }
}

} // namespace

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

    stopExistingFadeAnimation(target);
    target->show();

    if (!animationEnabled_) {
        if (auto *effect =
                qobject_cast<QGraphicsOpacityEffect *>(target->graphicsEffect())) {
            effect->setOpacity(1.0);
        }
        target->setWindowOpacity(1.0);
        return;
    }

    auto *effect = qobject_cast<QGraphicsOpacityEffect *>(target->graphicsEffect());
    const bool createdEffect = effect == nullptr;
    if (createdEffect) {
        effect = new QGraphicsOpacityEffect(target);
        effect->setOpacity(0.0);
        target->setGraphicsEffect(effect);
    }

    auto *animation = new QPropertyAnimation(effect, "opacity", target);
    animation->setObjectName(kFadeAnimationObjectName);
    animation->setDuration(duration);
    animation->setStartValue(createdEffect ? 0.0 : effect->opacity());
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    QObject::connect(
        animation,
        &QPropertyAnimation::finished,
        animation,
        &QObject::deleteLater);
    animation->start();
}

void QelAnimationHelper::fadeOut(QWidget *target, int duration)
{
    if (target == nullptr) {
        return;
    }

    stopExistingFadeAnimation(target);

    if (!animationEnabled_) {
        target->hide();
        return;
    }

    auto *effect = qobject_cast<QGraphicsOpacityEffect *>(target->graphicsEffect());
    const bool createdEffect = effect == nullptr;
    if (createdEffect) {
        effect = new QGraphicsOpacityEffect(target);
        effect->setOpacity(1.0);
        target->setGraphicsEffect(effect);
    }

    auto *animation = new QPropertyAnimation(effect, "opacity", target);
    animation->setObjectName(kFadeAnimationObjectName);
    animation->setDuration(duration);
    animation->setStartValue(createdEffect ? 1.0 : effect->opacity());
    animation->setEndValue(0.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    QPointer<QWidget> safeTarget(target);
    QObject::connect(animation, &QPropertyAnimation::finished, target, [safeTarget]() {
        if (safeTarget != nullptr) {
            safeTarget->hide();
        }
    });
    QObject::connect(
        animation,
        &QPropertyAnimation::finished,
        animation,
        &QObject::deleteLater);

    animation->start();
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
