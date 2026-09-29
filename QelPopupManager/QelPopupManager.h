#ifndef QELPOPUPMANAGER_H
#define QELPOPUPMANAGER_H

#include <QList>
#include <QPoint>
#include <QPointer>
#include <QSize>

class QWidget;

namespace qel {

enum class PopupPlacement {
    TopStart,
    Top,
    TopEnd,
    BottomStart,
    Bottom,
    BottomEnd,
    LeftStart,
    Left,
    LeftEnd,
    RightStart,
    Right,
    RightEnd
};

enum class PopupType {
    Tooltip,
    Popover,
    Dropdown,
    Dialog,
    Drawer,
    Message,
    MessageBox,
    Notification,
    Custom
};

struct PopupPolicy {
    PopupType type = PopupType::Custom;
    bool closeOnOutsideClick = true;
    bool closeOnEsc = true;
    bool exclusive = false;
};

class QelPopupManager {
public:
    static QPoint computePopupPosition(QWidget *anchor,
                                       QSize popupSize,
                                       PopupPlacement placement,
                                       int offset = 0,
                                       PopupPlacement *resolvedPlacement = nullptr);

    static QPoint computePopupPosition(QWidget *anchor,
                                       QSize popupSize,
                                       PopupPlacement placement,
                                       int offset,
                                       const QList<PopupPlacement> &fallbackPlacements,
                                       int boundariesPadding,
                                       PopupPlacement *resolvedPlacement = nullptr);

    static int acquireZIndex(PopupType type);
    static void registerPopup(QWidget *popup, PopupPolicy policy = PopupPolicy());
    static void closeAll(PopupType type);
    static void handleScreenBoundary(QWidget *popup);

private:
    struct PopupRecord {
        QPointer<QWidget> popup;
        PopupPolicy policy;
    };

    static QList<PopupRecord> popups_;
    static int zIndexSeed_;
};

} // namespace qel

#endif // QELPOPUPMANAGER_H
