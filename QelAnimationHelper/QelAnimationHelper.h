#ifndef QELANIMATIONHELPER_H
#define QELANIMATIONHELPER_H

#include <QEasingCurve>

class QWidget;

namespace qel {

class QelAnimationHelper {
public:
    static void setAnimationEnabled(bool enabled);
    static bool isAnimationEnabled();

    static void fadeIn(QWidget *target, int duration = 160);
    static void fadeOut(QWidget *target, int duration = 120);
    static void pressFeedback(QWidget *target, int duration = 100);
    static void focusRingPulse(QWidget *target, int duration = 180,
                               QEasingCurve::Type easing = QEasingCurve::OutCubic);

private:
    static bool animationEnabled_;
};

} // namespace qel

#endif // QELANIMATIONHELPER_H
