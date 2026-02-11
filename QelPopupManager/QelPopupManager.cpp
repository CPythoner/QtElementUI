#include "QelPopupManager.h"

#include <QApplication>
#include <QScreen>
#include <QWidget>

namespace qel {

QList<QelPopupManager::PopupRecord> QelPopupManager::popups_;
int QelPopupManager::zIndexSeed_ = 2000;

QPoint QelPopupManager::computePopupPosition(QWidget *anchor, QSize popupSize, PopupPlacement placement)
{
    if (anchor == nullptr) {
        return QPoint(0, 0);
    }

    const QRect anchorRect = anchor->rect();
    const QPoint anchorTopLeft = anchor->mapToGlobal(anchorRect.topLeft());

    QPoint result = anchorTopLeft;
    switch (placement) {
    case PopupPlacement::Top:
        result = QPoint(anchorTopLeft.x(), anchorTopLeft.y() - popupSize.height());
        break;
    case PopupPlacement::Left:
        result = QPoint(anchorTopLeft.x() - popupSize.width(), anchorTopLeft.y());
        break;
    case PopupPlacement::Right:
        result = QPoint(anchorTopLeft.x() + anchorRect.width(), anchorTopLeft.y());
        break;
    case PopupPlacement::Bottom:
    default:
        result = QPoint(anchorTopLeft.x(), anchorTopLeft.y() + anchorRect.height());
        break;
    }

    QScreen *screen = anchor->screen();
    if (screen == nullptr) {
        screen = QApplication::primaryScreen();
    }

    if (screen != nullptr) {
        const QRect avail = screen->availableGeometry();

        if (result.x() + popupSize.width() > avail.right()) {
            result.setX(avail.right() - popupSize.width());
        }
        if (result.x() < avail.left()) {
            result.setX(avail.left());
        }

        if (result.y() + popupSize.height() > avail.bottom()) {
            const int topY = anchorTopLeft.y() - popupSize.height();
            result.setY(topY >= avail.top() ? topY : (avail.bottom() - popupSize.height()));
        }
        if (result.y() < avail.top()) {
            result.setY(avail.top());
        }
    }

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

    const QRect avail = screen->availableGeometry();
    QRect g = popup->geometry();

    if (g.right() > avail.right()) {
        g.moveRight(avail.right());
    }
    if (g.left() < avail.left()) {
        g.moveLeft(avail.left());
    }
    if (g.bottom() > avail.bottom()) {
        g.moveBottom(avail.bottom());
    }
    if (g.top() < avail.top()) {
        g.moveTop(avail.top());
    }

    popup->setGeometry(g);
}

} // namespace qel
