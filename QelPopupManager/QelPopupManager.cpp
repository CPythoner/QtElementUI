#include "QelPopupManager.h"

#include <QApplication>
#include <QScreen>
#include <QWidget>

namespace qel {

namespace {

bool isTop(PopupPlacement placement)
{
    return placement == PopupPlacement::TopStart
        || placement == PopupPlacement::Top
        || placement == PopupPlacement::TopEnd;
}

bool isBottom(PopupPlacement placement)
{
    return placement == PopupPlacement::BottomStart
        || placement == PopupPlacement::Bottom
        || placement == PopupPlacement::BottomEnd;
}

bool isLeft(PopupPlacement placement)
{
    return placement == PopupPlacement::LeftStart
        || placement == PopupPlacement::Left
        || placement == PopupPlacement::LeftEnd;
}

PopupPlacement oppositePlacement(PopupPlacement placement)
{
    switch (placement) {
    case PopupPlacement::TopStart:
        return PopupPlacement::BottomStart;
    case PopupPlacement::Top:
        return PopupPlacement::Bottom;
    case PopupPlacement::TopEnd:
        return PopupPlacement::BottomEnd;
    case PopupPlacement::BottomStart:
        return PopupPlacement::TopStart;
    case PopupPlacement::Bottom:
        return PopupPlacement::Top;
    case PopupPlacement::BottomEnd:
        return PopupPlacement::TopEnd;
    case PopupPlacement::LeftStart:
        return PopupPlacement::RightStart;
    case PopupPlacement::Left:
        return PopupPlacement::Right;
    case PopupPlacement::LeftEnd:
        return PopupPlacement::RightEnd;
    case PopupPlacement::RightStart:
        return PopupPlacement::LeftStart;
    case PopupPlacement::Right:
        return PopupPlacement::Left;
    case PopupPlacement::RightEnd:
        return PopupPlacement::LeftEnd;
    }

    return PopupPlacement::Bottom;
}

QPoint candidatePosition(const QRect &anchorRect,
                         const QSize &popupSize,
                         PopupPlacement placement,
                         int offset)
{
    const int centeredX = anchorRect.center().x() - popupSize.width() / 2;
    const int centeredY = anchorRect.center().y() - popupSize.height() / 2;

    switch (placement) {
    case PopupPlacement::TopStart:
        return QPoint(anchorRect.left(), anchorRect.top() - popupSize.height() - offset);
    case PopupPlacement::Top:
        return QPoint(centeredX, anchorRect.top() - popupSize.height() - offset);
    case PopupPlacement::TopEnd:
        return QPoint(anchorRect.right() - popupSize.width() + 1,
                      anchorRect.top() - popupSize.height() - offset);
    case PopupPlacement::BottomStart:
        return QPoint(anchorRect.left(), anchorRect.bottom() + 1 + offset);
    case PopupPlacement::Bottom:
        return QPoint(centeredX, anchorRect.bottom() + 1 + offset);
    case PopupPlacement::BottomEnd:
        return QPoint(anchorRect.right() - popupSize.width() + 1,
                      anchorRect.bottom() + 1 + offset);
    case PopupPlacement::LeftStart:
        return QPoint(anchorRect.left() - popupSize.width() - offset, anchorRect.top());
    case PopupPlacement::Left:
        return QPoint(anchorRect.left() - popupSize.width() - offset, centeredY);
    case PopupPlacement::LeftEnd:
        return QPoint(anchorRect.left() - popupSize.width() - offset,
                      anchorRect.bottom() - popupSize.height() + 1);
    case PopupPlacement::RightStart:
        return QPoint(anchorRect.right() + 1 + offset, anchorRect.top());
    case PopupPlacement::Right:
        return QPoint(anchorRect.right() + 1 + offset, centeredY);
    case PopupPlacement::RightEnd:
        return QPoint(anchorRect.right() + 1 + offset,
                      anchorRect.bottom() - popupSize.height() + 1);
    }

    return QPoint(anchorRect.left(), anchorRect.bottom() + 1 + offset);
}

bool overflowsMainAxis(const QPoint &position,
                       const QSize &popupSize,
                       PopupPlacement placement,
                       const QRect &available)
{
    if (isTop(placement)) {
        return position.y() < available.top();
    }
    if (isBottom(placement)) {
        return position.y() + popupSize.height() - 1 > available.bottom();
    }
    if (isLeft(placement)) {
        return position.x() < available.left();
    }

    return position.x() + popupSize.width() - 1 > available.right();
}

QRect paddedAvailableGeometry(QScreen *screen, int padding)
{
    QRect available = screen->availableGeometry();
    const int safePadding = qMax(0, padding);
    const QRect padded =
        available.adjusted(safePadding, safePadding, -safePadding, -safePadding);

    return padded.isValid() ? padded : available;
}

} // namespace

QList<QelPopupManager::PopupRecord> QelPopupManager::popups_;
int QelPopupManager::zIndexSeed_ = 2000;

QPoint QelPopupManager::computePopupPosition(QWidget *anchor,
                                             QSize popupSize,
                                             PopupPlacement placement,
                                             int offset,
                                             PopupPlacement *resolvedPlacement)
{
    return computePopupPosition(
        anchor,
        popupSize,
        placement,
        offset,
        QList<PopupPlacement>(),
        0,
        resolvedPlacement);
}

QPoint QelPopupManager::computePopupPosition(
    QWidget *anchor,
    QSize popupSize,
    PopupPlacement placement,
    int offset,
    const QList<PopupPlacement> &fallbackPlacements,
    int boundariesPadding,
    PopupPlacement *resolvedPlacement)
{
    if (resolvedPlacement != nullptr) {
        *resolvedPlacement = placement;
    }

    if (anchor == nullptr) {
        return QPoint(0, 0);
    }

    const QPoint globalTopLeft = anchor->mapToGlobal(QPoint(0, 0));
    const QRect anchorRect(globalTopLeft, anchor->size());

    QScreen *screen = anchor->screen();
    if (screen == nullptr) {
        screen = QApplication::primaryScreen();
    }

    QPoint result = candidatePosition(anchorRect, popupSize, placement, offset);

    if (screen == nullptr) {
        return result;
    }

    const QRect available =
        paddedAvailableGeometry(screen, boundariesPadding);

    QList<PopupPlacement> candidates;
    candidates.append(placement);

    if (fallbackPlacements.isEmpty()) {
        candidates.append(oppositePlacement(placement));
    } else {
        for (PopupPlacement fallback : fallbackPlacements) {
            if (!candidates.contains(fallback)) {
                candidates.append(fallback);
            }
        }
    }

    for (PopupPlacement candidate : candidates) {
        const QPoint candidatePoint =
            candidatePosition(anchorRect, popupSize, candidate, offset);

        if (!overflowsMainAxis(
                candidatePoint,
                popupSize,
                candidate,
                available)) {
            result = candidatePoint;
            if (resolvedPlacement != nullptr) {
                *resolvedPlacement = candidate;
            }
            break;
        }
    }

    const int maxX = qMax(
        available.left(),
        available.right() - popupSize.width() + 1);
    const int maxY = qMax(
        available.top(),
        available.bottom() - popupSize.height() + 1);

    result.setX(qBound(available.left(), result.x(), maxX));
    result.setY(qBound(available.top(), result.y(), maxY));

    return result;
}

int QelPopupManager::acquireZIndex(PopupType)
{
    ++zIndexSeed_;
    return zIndexSeed_;
}

void QelPopupManager::registerPopup(QWidget *popup, PopupPolicy policy)
{
    if (popup == nullptr) {
        return;
    }

    for (int i = popups_.size() - 1; i >= 0; --i) {
        if (popups_.at(i).popup == nullptr) {
            popups_.removeAt(i);
        }
    }

    if (policy.exclusive) {
        closeAll(policy.type);
    }

    for (int i = 0; i < popups_.size(); ++i) {
        if (popups_.at(i).popup == popup) {
            popups_[i].policy = policy;
            return;
        }
    }

    popups_.append({popup, policy});
}

void QelPopupManager::closeAll(PopupType type)
{
    for (int i = popups_.size() - 1; i >= 0; --i) {
        PopupRecord &record = popups_[i];
        if (record.popup == nullptr) {
            popups_.removeAt(i);
            continue;
        }

        if (record.policy.type == type) {
            record.popup->hide();
        }
    }
}

void QelPopupManager::handleScreenBoundary(QWidget *popup)
{
    if (popup == nullptr) {
        return;
    }

    QScreen *screen = popup->screen();
    if (screen == nullptr) {
        screen = QApplication::primaryScreen();
    }
    if (screen == nullptr) {
        return;
    }

    const QRect available = screen->availableGeometry();
    QRect geometry = popup->geometry();

    if (geometry.right() > available.right()) {
        geometry.moveRight(available.right());
    }
    if (geometry.left() < available.left()) {
        geometry.moveLeft(available.left());
    }
    if (geometry.bottom() > available.bottom()) {
        geometry.moveBottom(available.bottom());
    }
    if (geometry.top() < available.top()) {
        geometry.moveTop(available.top());
    }

    popup->setGeometry(geometry);
}

} // namespace qel
