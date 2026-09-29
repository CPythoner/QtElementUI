#include "QelTooltip.h"

#include "../QelAnimationHelper/QelAnimationHelper.h"
#include "../QelPopupManager/QelPopupManager.h"
#include "../QelTheme/QelTheme.h"

#include <QApplication>
#include <QContextMenuEvent>
#include <QEvent>
#include <functional>
#include <QKeyEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPalette>
#include <QPolygonF>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

namespace qel {

namespace {

constexpr int kArrowSize = 6;
constexpr int kHorizontalPadding = 10;
constexpr int kVerticalPadding = 10;
constexpr int kFadeCleanupDelay = 160;

PopupPlacement toPopupPlacement(QelTooltip::Placement placement)
{
    switch (placement) {
    case QelTooltip::Placement::TopStart:
        return PopupPlacement::TopStart;
    case QelTooltip::Placement::Top:
        return PopupPlacement::Top;
    case QelTooltip::Placement::TopEnd:
        return PopupPlacement::TopEnd;
    case QelTooltip::Placement::BottomStart:
        return PopupPlacement::BottomStart;
    case QelTooltip::Placement::Bottom:
        return PopupPlacement::Bottom;
    case QelTooltip::Placement::BottomEnd:
        return PopupPlacement::BottomEnd;
    case QelTooltip::Placement::LeftStart:
        return PopupPlacement::LeftStart;
    case QelTooltip::Placement::Left:
        return PopupPlacement::Left;
    case QelTooltip::Placement::LeftEnd:
        return PopupPlacement::LeftEnd;
    case QelTooltip::Placement::RightStart:
        return PopupPlacement::RightStart;
    case QelTooltip::Placement::Right:
        return PopupPlacement::Right;
    case QelTooltip::Placement::RightEnd:
        return PopupPlacement::RightEnd;
    }

    return PopupPlacement::Bottom;
}

QList<PopupPlacement> toPopupPlacements(
    const QList<QelTooltip::Placement> &placements)
{
    QList<PopupPlacement> result;
    for (QelTooltip::Placement placement : placements) {
        result.append(toPopupPlacement(placement));
    }
    return result;
}

QelTooltip::Placement fromPopupPlacement(PopupPlacement placement)
{
    switch (placement) {
    case PopupPlacement::TopStart:
        return QelTooltip::Placement::TopStart;
    case PopupPlacement::Top:
        return QelTooltip::Placement::Top;
    case PopupPlacement::TopEnd:
        return QelTooltip::Placement::TopEnd;
    case PopupPlacement::BottomStart:
        return QelTooltip::Placement::BottomStart;
    case PopupPlacement::Bottom:
        return QelTooltip::Placement::Bottom;
    case PopupPlacement::BottomEnd:
        return QelTooltip::Placement::BottomEnd;
    case PopupPlacement::LeftStart:
        return QelTooltip::Placement::LeftStart;
    case PopupPlacement::Left:
        return QelTooltip::Placement::Left;
    case PopupPlacement::LeftEnd:
        return QelTooltip::Placement::LeftEnd;
    case PopupPlacement::RightStart:
        return QelTooltip::Placement::RightStart;
    case PopupPlacement::Right:
        return QelTooltip::Placement::Right;
    case PopupPlacement::RightEnd:
        return QelTooltip::Placement::RightEnd;
    }

    return QelTooltip::Placement::Bottom;
}

bool isTop(QelTooltip::Placement placement)
{
    return placement == QelTooltip::Placement::TopStart
        || placement == QelTooltip::Placement::Top
        || placement == QelTooltip::Placement::TopEnd;
}

bool isBottom(QelTooltip::Placement placement)
{
    return placement == QelTooltip::Placement::BottomStart
        || placement == QelTooltip::Placement::Bottom
        || placement == QelTooltip::Placement::BottomEnd;
}

bool isLeft(QelTooltip::Placement placement)
{
    return placement == QelTooltip::Placement::LeftStart
        || placement == QelTooltip::Placement::Left
        || placement == QelTooltip::Placement::LeftEnd;
}

bool pointInWidget(const QWidget *widget, const QPoint &globalPoint)
{
    if (widget == nullptr || !widget->isVisible()) {
        return false;
    }

    const QPoint topLeft = widget->mapToGlobal(QPoint(0, 0));
    return QRect(topLeft, widget->size()).contains(globalPoint);
}

} // namespace

class QelTooltipOutsideFilter : public QObject
{
public:
    explicit QelTooltipOutsideFilter(
        const std::function<void(const QPoint &)> &callback,
        QObject *parent = nullptr)
        : QObject(parent)
        , callback_(callback)
    {
    }

protected:
    bool eventFilter(QObject *watched, QEvent *event) override
    {
        Q_UNUSED(watched);

        if (!callback_) {
            return false;
        }

        if (event->type() == QEvent::MouseButtonPress) {
            const QMouseEvent *mouseEvent =
                static_cast<QMouseEvent *>(event);
            callback_(mouseEvent->globalPos());
        } else if (event->type() == QEvent::ContextMenu) {
            const QContextMenuEvent *contextEvent =
                static_cast<QContextMenuEvent *>(event);
            callback_(contextEvent->globalPos());
        }

        return false;
    }

private:
    std::function<void(const QPoint &)> callback_;
};

class QelTooltipPopup : public QWidget
{
public:
    explicit QelTooltipPopup()
        : QWidget(nullptr,
                  Qt::ToolTip
                      | Qt::FramelessWindowHint
                      | Qt::NoDropShadowWindowHint)
    {
        setAttribute(Qt::WA_TranslucentBackground, true);
        setAttribute(Qt::WA_ShowWithoutActivating, true);
        setMouseTracking(true);

        layout_ = new QVBoxLayout(this);
        layout_->setSpacing(0);

        label_ = new QLabel(this);
        label_->setTextFormat(Qt::PlainText);
        label_->setTextInteractionFlags(Qt::NoTextInteraction);
        label_->setWordWrap(false);
        layout_->addWidget(label_);

        refreshLayoutMargins();
        applyLabelStyle();
    }

    void setEffect(QelTooltip::Effect effect)
    {
        if (effect_ == effect) {
            return;
        }

        effect_ = effect;
        applyLabelStyle();
        update();
    }

    void setContent(const QString &content)
    {
        label_->setText(content);
        if (customContent_ == nullptr) {
            label_->show();
        }
        adjustSize();
        update();
    }

    void setRawContent(bool rawContent)
    {
        rawContent_ = rawContent;
        label_->setTextFormat(rawContent_ ? Qt::RichText : Qt::PlainText);
        adjustSize();
        update();
    }

    void setContentWidget(QWidget *widget)
    {
        if (customContent_ == widget) {
            return;
        }

        if (customContent_ != nullptr) {
            layout_->removeWidget(customContent_);
            customContent_->hide();
            customContent_->deleteLater();
            customContent_ = nullptr;
        }

        if (widget == nullptr) {
            label_->show();
            adjustSize();
            return;
        }

        label_->hide();
        customContent_ = widget;
        customContent_->setParent(this);
        customContent_->setPalette(palette());
        layout_->addWidget(customContent_);
        customContent_->show();
        adjustSize();
    }

    QWidget *takeContentWidget()
    {
        if (customContent_ == nullptr) {
            return nullptr;
        }

        QWidget *widget = customContent_;
        layout_->removeWidget(widget);
        widget->hide();
        widget->setParent(nullptr);
        customContent_ = nullptr;
        label_->show();
        adjustSize();
        return widget;
    }

    QWidget *contentWidget() const
    {
        return customContent_;
    }

    void setPlacement(QelTooltip::Placement placement)
    {
        if (placement_ == placement) {
            return;
        }

        placement_ = placement;
        refreshLayoutMargins();
        adjustSize();
        update();
    }

    void setShowArrow(bool show)
    {
        if (showArrow_ == show) {
            return;
        }

        showArrow_ = show;
        refreshLayoutMargins();
        adjustSize();
        update();
    }

    void setArrowTarget(const QPoint &globalTarget)
    {
        arrowTargetGlobal_ = globalTarget;
        update();
    }

    void setArrowOffset(int offset)
    {
        arrowOffset_ = qMax(0, offset);
        update();
    }

    void setEnterable(bool enterable)
    {
        setAttribute(Qt::WA_TransparentForMouseEvents, !enterable);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);

        const QelTheme::ColorTokens &colors = QelTheme::colors();
        const QColor background =
            effect_ == QelTooltip::Effect::Dark
                ? QColor(colors.textPrimary)
                : QColor(colors.fillBlank);
        const QColor border =
            effect_ == QelTooltip::Effect::Dark
                ? background
                : QColor(colors.textPrimary);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        QRectF bubble = rect().adjusted(0.5, 0.5, -0.5, -0.5);
        if (showArrow_) {
            if (isTop(placement_)) {
                bubble.adjust(0.0, 0.0, 0.0, -kArrowSize);
            } else if (isBottom(placement_)) {
                bubble.adjust(0.0, kArrowSize, 0.0, 0.0);
            } else if (isLeft(placement_)) {
                bubble.adjust(0.0, 0.0, -kArrowSize, 0.0);
            } else {
                bubble.adjust(kArrowSize, 0.0, 0.0, 0.0);
            }
        }

        painter.setPen(QPen(border, 1.0));
        painter.setBrush(background);
        painter.drawRoundedRect(bubble, 4.0, 4.0);

        if (!showArrow_) {
            return;
        }

        const QPoint localTarget = mapFromGlobal(arrowTargetGlobal_);
        const qreal arrowPadding =
            qMax<qreal>(8.0, kArrowSize + arrowOffset_);
        QPolygonF arrow;

        if (isTop(placement_)) {
            const qreal x = qBound<qreal>(
                bubble.left() + arrowPadding,
                localTarget.x(),
                bubble.right() - arrowPadding);
            arrow << QPointF(x - kArrowSize, bubble.bottom() - 0.5)
                  << QPointF(x + kArrowSize, bubble.bottom() - 0.5)
                  << QPointF(x, rect().bottom() - 0.5);
        } else if (isBottom(placement_)) {
            const qreal x = qBound<qreal>(
                bubble.left() + arrowPadding,
                localTarget.x(),
                bubble.right() - arrowPadding);
            arrow << QPointF(x - kArrowSize, bubble.top() + 0.5)
                  << QPointF(x + kArrowSize, bubble.top() + 0.5)
                  << QPointF(x, rect().top() + 0.5);
        } else if (isLeft(placement_)) {
            const qreal y = qBound<qreal>(
                bubble.top() + arrowPadding,
                localTarget.y(),
                bubble.bottom() - arrowPadding);
            arrow << QPointF(bubble.right() - 0.5, y - kArrowSize)
                  << QPointF(bubble.right() - 0.5, y + kArrowSize)
                  << QPointF(rect().right() - 0.5, y);
        } else {
            const qreal y = qBound<qreal>(
                bubble.top() + arrowPadding,
                localTarget.y(),
                bubble.bottom() - arrowPadding);
            arrow << QPointF(bubble.left() + 0.5, y - kArrowSize)
                  << QPointF(bubble.left() + 0.5, y + kArrowSize)
                  << QPointF(rect().left() + 0.5, y);
        }

        painter.drawPolygon(arrow);
    }

private:
    void applyLabelStyle()
    {
        const QelTheme::ColorTokens &colors = QelTheme::colors();
        const QString foreground =
            effect_ == QelTooltip::Effect::Dark
                ? colors.fillBlank
                : colors.textPrimary;

        QPalette popupPalette = palette();
        popupPalette.setColor(QPalette::WindowText, QColor(foreground));
        setPalette(popupPalette);

        label_->setPalette(popupPalette);
        label_->setStyleSheet(
            QString(
                "QLabel { color: %1; background: transparent; "
                "border: none; font-size: 12px; }")
                .arg(foreground));

        if (customContent_ != nullptr) {
            customContent_->setPalette(popupPalette);
        }
    }

    void refreshLayoutMargins()
    {
        int left = kHorizontalPadding;
        int top = kVerticalPadding;
        int right = kHorizontalPadding;
        int bottom = kVerticalPadding;

        if (showArrow_) {
            if (isTop(placement_)) {
                bottom += kArrowSize;
            } else if (isBottom(placement_)) {
                top += kArrowSize;
            } else if (isLeft(placement_)) {
                right += kArrowSize;
            } else {
                left += kArrowSize;
            }
        }

        layout_->setContentsMargins(left, top, right, bottom);
    }

    QVBoxLayout *layout_ = nullptr;
    QLabel *label_ = nullptr;
    QWidget *customContent_ = nullptr;

    QelTooltip::Effect effect_ = QelTooltip::Effect::Dark;
    QelTooltip::Placement placement_ = QelTooltip::Placement::Bottom;
    bool rawContent_ = false;
    bool showArrow_ = true;
    int arrowOffset_ = 5;
    QPoint arrowTargetGlobal_;
};

QelTooltip::QelTooltip(QWidget *target, QObject *parent)
    : QObject(parent)
{
    outsideFilter_ = new QelTooltipOutsideFilter(
        [this](const QPoint &globalPoint) {
            if (!visible_) {
                return;
            }

            if (pointInWidget(target_, globalPoint)
                || pointInWidget(popup_, globalPoint)) {
                return;
            }

            requestHide();
        },
        this);

    triggerKeys_ = {
        Qt::Key_Return,
        Qt::Key_Enter,
        Qt::Key_Space
    };

    showTimer_ = new QTimer(this);
    showTimer_->setSingleShot(true);
    connect(showTimer_, &QTimer::timeout, this, &QelTooltip::showNow);

    hideTimer_ = new QTimer(this);
    hideTimer_->setSingleShot(true);
    connect(hideTimer_, &QTimer::timeout, this, [this]() {
        if (enterable_
            && hasTrigger(Trigger::Hover)
            && popup_ != nullptr
            && popup_->underMouse()) {
            return;
        }
        hideNow();
    });

    autoCloseTimer_ = new QTimer(this);
    autoCloseTimer_->setSingleShot(true);
    connect(
        autoCloseTimer_,
        &QTimer::timeout,
        this,
        &QelTooltip::hideNow);

    attachTarget(target);
}

QelTooltip::~QelTooltip()
{
    if (qApp != nullptr && outsideFilter_ != nullptr) {
        qApp->removeEventFilter(outsideFilter_);
    }

    restoreTargetFocusPolicy();

    if (popup_ != nullptr) {
        delete popup_;
        popup_ = nullptr;
    }

    if (contentWidget_ != nullptr) {
        delete contentWidget_;
        contentWidget_.clear();
    }
}

void QelTooltip::setTarget(QWidget *target)
{
    if (target_ == target) {
        return;
    }

    restoreTargetFocusPolicy();

    if (target_ != nullptr) {
        target_->removeEventFilter(this);
    }
    if (targetWindow_ != nullptr && targetWindow_ != target_) {
        targetWindow_->removeEventFilter(this);
    }

    target_.clear();
    targetWindow_.clear();
    hideNow();
    attachTarget(target);
}

QWidget *QelTooltip::target() const
{
    return target_;
}

void QelTooltip::setEffect(Effect effect)
{
    effect_ = effect;
    updatePopup();
}

QelTooltip::Effect QelTooltip::effect() const
{
    return effect_;
}

void QelTooltip::setContent(const QString &content)
{
    content_ = content;
    updatePopup();

    if (visible_) {
        positionPopup();
    }
}

QString QelTooltip::content() const
{
    return content_;
}

void QelTooltip::setRawContent(bool rawContent)
{
    rawContent_ = rawContent;
    updatePopup();

    if (visible_) {
        positionPopup();
    }
}

bool QelTooltip::rawContent() const
{
    return rawContent_;
}

void QelTooltip::setContentWidget(QWidget *widget)
{
    ensurePopup();
    contentWidget_ = widget;
    popup_->setContentWidget(widget);

    if (visible_) {
        positionPopup();
    }
}

QWidget *QelTooltip::contentWidget() const
{
    return contentWidget_;
}

void QelTooltip::setPlacement(Placement placement)
{
    placement_ = placement;
    updatePopup();

    if (visible_) {
        positionPopup();
    }
}

QelTooltip::Placement QelTooltip::placement() const
{
    return placement_;
}

void QelTooltip::setFallbackPlacements(
    const QList<Placement> &placements)
{
    fallbackPlacements_ = placements;

    if (visible_) {
        positionPopup();
    }
}

QList<QelTooltip::Placement> QelTooltip::fallbackPlacements() const
{
    return fallbackPlacements_;
}

void QelTooltip::setBoundariesPadding(int padding)
{
    boundariesPadding_ = qMax(0, padding);

    if (visible_) {
        positionPopup();
    }
}

int QelTooltip::boundariesPadding() const
{
    return boundariesPadding_;
}

void QelTooltip::setVisible(bool visible)
{
    if (visible) {
        showNow();
    } else {
        hideNow();
    }
}

bool QelTooltip::isVisible() const
{
    return visible_;
}

void QelTooltip::setDisabled(bool disabled)
{
    disabled_ = disabled;

    if (disabled_) {
        showTimer_->stop();
        hideNow();
    }
}

bool QelTooltip::isDisabled() const
{
    return disabled_;
}

void QelTooltip::setOffset(int offset)
{
    offset_ = offset;

    if (visible_) {
        positionPopup();
    }
}

int QelTooltip::offset() const
{
    return offset_;
}

void QelTooltip::setTransition(const QString &transition)
{
    transition_ = transition;
}

QString QelTooltip::transition() const
{
    return transition_;
}

void QelTooltip::setShowArrow(bool show)
{
    showArrow_ = show;
    updatePopup();

    if (visible_) {
        positionPopup();
    }
}

bool QelTooltip::showArrow() const
{
    return showArrow_;
}

void QelTooltip::setArrowOffset(int offset)
{
    arrowOffset_ = qMax(0, offset);

    if (popup_ != nullptr) {
        popup_->setArrowOffset(arrowOffset_);
    }
}

int QelTooltip::arrowOffset() const
{
    return arrowOffset_;
}

void QelTooltip::setShowAfter(int milliseconds)
{
    showAfter_ = qMax(0, milliseconds);
}

int QelTooltip::showAfter() const
{
    return showAfter_;
}

void QelTooltip::setHideAfter(int milliseconds)
{
    hideAfter_ = qMax(0, milliseconds);
}

int QelTooltip::hideAfter() const
{
    return hideAfter_;
}

void QelTooltip::setAutoClose(int milliseconds)
{
    autoClose_ = qMax(0, milliseconds);

    if (visible_) {
        autoCloseTimer_->stop();
        if (autoClose_ > 0) {
            autoCloseTimer_->start(autoClose_);
        }
    }
}

int QelTooltip::autoClose() const
{
    return autoClose_;
}

void QelTooltip::setTrigger(Trigger trigger)
{
    setTriggers(Triggers(trigger));
}

void QelTooltip::setTriggers(Triggers triggers)
{
    triggers_ = triggers;
}

QelTooltip::Triggers QelTooltip::triggers() const
{
    return triggers_;
}

void QelTooltip::setTriggerKeys(const QList<int> &keys)
{
    triggerKeys_ = keys;
}

QList<int> QelTooltip::triggerKeys() const
{
    return triggerKeys_;
}

void QelTooltip::setFocusOnTarget(bool enabled)
{
    focusOnTarget_ = enabled;
}

bool QelTooltip::focusOnTarget() const
{
    return focusOnTarget_;
}

void QelTooltip::setPersistent(bool persistent)
{
    persistent_ = persistent;

    if (!persistent_) {
        destroyPopupIfInactive();
    }
}

bool QelTooltip::isPersistent() const
{
    return persistent_;
}

void QelTooltip::setPopperClass(const QString &className)
{
    popperClass_ = className;

    if (popup_ != nullptr) {
        popup_->setProperty("qel-popper-class", popperClass_);
    }
}

QString QelTooltip::popperClass() const
{
    return popperClass_;
}

void QelTooltip::setPopperStyle(const QString &styleSheet)
{
    popperStyle_ = styleSheet;

    if (popup_ != nullptr) {
        popup_->setStyleSheet(popperStyle_);
    }
}

QString QelTooltip::popperStyle() const
{
    return popperStyle_;
}

void QelTooltip::setEnterable(bool enterable)
{
    enterable_ = enterable;

    if (popup_ != nullptr) {
        popup_->setEnterable(enterable_);
    }
}

bool QelTooltip::isEnterable() const
{
    return enterable_;
}

void QelTooltip::setTabIndex(int tabIndex)
{
    tabIndex_ = tabIndex;

    if (target_ == nullptr) {
        return;
    }

    if (tabIndex_ < 0) {
        target_->setFocusPolicy(Qt::NoFocus);
    } else {
        target_->setFocusPolicy(Qt::StrongFocus);
    }
}

int QelTooltip::tabIndex() const
{
    return tabIndex_;
}

void QelTooltip::show()
{
    showNow();
}

void QelTooltip::hide()
{
    hideNow();
}

void QelTooltip::toggle()
{
    if (visible_) {
        requestHide();
    } else {
        requestShow();
    }
}

bool QelTooltip::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == target_) {
        switch (event->type()) {
        case QEvent::Enter:
            if (hasTrigger(Trigger::Hover)) {
                requestShow();
                if (focusOnTarget_ && target_ != nullptr) {
                    target_->setFocus(Qt::MouseFocusReason);
                }
            }
            break;

        case QEvent::Leave:
            if (hasTrigger(Trigger::Hover)) {
                requestHide();
            }
            break;

        case QEvent::FocusIn:
            if (hasTrigger(Trigger::Focus)) {
                requestShow();
            }
            break;

        case QEvent::FocusOut:
            if (hasTrigger(Trigger::Focus)) {
                requestHide();
            }
            break;

        case QEvent::MouseButtonRelease: {
            const QMouseEvent *mouseEvent =
                static_cast<QMouseEvent *>(event);
            if (hasTrigger(Trigger::Click)
                && mouseEvent->button() == Qt::LeftButton) {
                toggle();
            }
            break;
        }

        case QEvent::ContextMenu:
            if (hasTrigger(Trigger::ContextMenu)) {
                toggle();
                event->accept();
                return true;
            }
            break;

        case QEvent::KeyPress: {
            const QKeyEvent *keyEvent =
                static_cast<QKeyEvent *>(event);
            if (triggerKeys_.contains(keyEvent->key())) {
                toggle();
                event->accept();
                return true;
            }
            break;
        }

        case QEvent::Move:
        case QEvent::Resize:
            if (visible_) {
                positionPopup();
            }
            break;

        case QEvent::Hide:
        case QEvent::Close:
            hideNow();
            break;

        case QEvent::Destroy:
            target_.clear();
            hideNow();
            break;

        default:
            break;
        }
    } else if (watched == targetWindow_) {
        if (visible_
            && (event->type() == QEvent::Move
                || event->type() == QEvent::Resize
                || event->type() == QEvent::WindowStateChange)) {
            positionPopup();
        }
    } else if (watched == popup_) {
        if (hasTrigger(Trigger::Hover)) {
            if (event->type() == QEvent::Enter && enterable_) {
                hideTimer_->stop();
            } else if (event->type() == QEvent::Leave) {
                requestHide();
            }
        }
    }

    return QObject::eventFilter(watched, event);
}

void QelTooltip::attachTarget(QWidget *target)
{
    target_ = target;
    if (target_ == nullptr) {
        return;
    }

    originalFocusPolicy_ = target_->focusPolicy();
    hasOriginalFocusPolicy_ = true;

    target_->installEventFilter(this);

    targetWindow_ = target_->window();
    if (targetWindow_ != nullptr && targetWindow_ != target_) {
        targetWindow_->installEventFilter(this);
    }

    setTabIndex(tabIndex_);
}

void QelTooltip::restoreTargetFocusPolicy()
{
    if (target_ != nullptr && hasOriginalFocusPolicy_) {
        target_->setFocusPolicy(originalFocusPolicy_);
    }

    hasOriginalFocusPolicy_ = false;
}

void QelTooltip::ensurePopup()
{
    if (popup_ != nullptr) {
        return;
    }

    popup_ = new QelTooltipPopup();
    popup_->installEventFilter(this);
    popup_->setProperty("qel-popper-class", popperClass_);
    popup_->setStyleSheet(popperStyle_);
    popup_->setProperty(
        "qel-z-index",
        QelPopupManager::acquireZIndex(PopupType::Tooltip));

    PopupPolicy policy;
    policy.type = PopupType::Tooltip;
    policy.closeOnOutsideClick = true;
    policy.closeOnEsc = true;
    policy.exclusive = false;
    QelPopupManager::registerPopup(popup_, policy);

    updatePopup();
}

void QelTooltip::updatePopup()
{
    if (popup_ == nullptr) {
        return;
    }

    popup_->setEffect(effect_);
    popup_->setRawContent(rawContent_);
    popup_->setContent(content_);
    popup_->setPlacement(placement_);
    popup_->setShowArrow(showArrow_);
    popup_->setArrowOffset(arrowOffset_);
    popup_->setEnterable(enterable_);

    if (contentWidget_ != nullptr
        && popup_->contentWidget() != contentWidget_) {
        popup_->setContentWidget(contentWidget_);
    }
}

void QelTooltip::positionPopup()
{
    if (target_ == nullptr || popup_ == nullptr) {
        return;
    }

    popup_->setPlacement(placement_);
    popup_->adjustSize();

    PopupPlacement resolvedPlacement = toPopupPlacement(placement_);
    const QPoint position =
        QelPopupManager::computePopupPosition(
            target_,
            popup_->size(),
            resolvedPlacement,
            offset_,
            toPopupPlacements(fallbackPlacements_),
            boundariesPadding_,
            &resolvedPlacement);

    popup_->move(position);
    popup_->setPlacement(fromPopupPlacement(resolvedPlacement));

    const QPoint anchorTopLeft =
        target_->mapToGlobal(QPoint(0, 0));
    const QRect anchorRect(anchorTopLeft, target_->size());
    popup_->setArrowTarget(anchorRect.center());

    QelPopupManager::handleScreenBoundary(popup_);
}

void QelTooltip::destroyPopupIfInactive()
{
    if (persistent_ || visible_ || popup_ == nullptr) {
        return;
    }

    if (contentWidget_ != nullptr
        && popup_->contentWidget() == contentWidget_) {
        popup_->takeContentWidget();
    }

    delete popup_;
    popup_ = nullptr;
}

void QelTooltip::requestShow()
{
    if (disabled_) {
        return;
    }

    hideTimer_->stop();

    if (showAfter_ <= 0) {
        showNow();
        return;
    }

    showTimer_->start(showAfter_);
}

void QelTooltip::requestHide()
{
    showTimer_->stop();
    autoCloseTimer_->stop();

    if (hideAfter_ <= 0) {
        hideNow();
        return;
    }

    hideTimer_->start(hideAfter_);
}

void QelTooltip::showNow()
{
    if (disabled_ || target_ == nullptr) {
        return;
    }

    ensurePopup();
    updatePopup();

    if (content_.isEmpty() && contentWidget_ == nullptr) {
        return;
    }

    hideTimer_->stop();
    positionPopup();
    popup_->raise();

    const bool changed = !visible_;
    if (changed) {
        emit beforeShow();
    }

    if (useFadeTransition()) {
        QelAnimationHelper::fadeIn(popup_);
    } else {
        popup_->show();
    }

    visible_ = true;

    if (qApp != nullptr
        && outsideFilter_ != nullptr
        && (hasTrigger(Trigger::Click)
            || hasTrigger(Trigger::ContextMenu))) {
        qApp->installEventFilter(outsideFilter_);
    }

    autoCloseTimer_->stop();
    if (autoClose_ > 0) {
        autoCloseTimer_->start(autoClose_);
    }

    if (changed) {
        emit visibilityChanged(true);
        emit shown();
    }
}

void QelTooltip::hideNow()
{
    showTimer_->stop();
    hideTimer_->stop();
    autoCloseTimer_->stop();

    if (!visible_) {
        destroyPopupIfInactive();
        return;
    }

    emit beforeHide();

    if (popup_ != nullptr && popup_->isVisible()) {
        if (useFadeTransition()) {
            QelAnimationHelper::fadeOut(popup_);
        } else {
            popup_->hide();
        }
    }

    visible_ = false;

    if (qApp != nullptr && outsideFilter_ != nullptr) {
        qApp->removeEventFilter(outsideFilter_);
    }

    emit visibilityChanged(false);
    emit hidden();

    if (!persistent_) {
        const int delay =
            useFadeTransition() ? kFadeCleanupDelay : 0;
        QTimer::singleShot(delay, this, [this]() {
            destroyPopupIfInactive();
        });
    }
}

bool QelTooltip::hasTrigger(Trigger trigger) const
{
    return triggers_.testFlag(trigger);
}

bool QelTooltip::useFadeTransition() const
{
    return !transition_.trimmed().isEmpty()
        && transition_.compare("none", Qt::CaseInsensitive) != 0;
}

} // namespace qel
