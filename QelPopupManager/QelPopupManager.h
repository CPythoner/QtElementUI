#ifndef QELPOPUPMANAGER_H
#define QELPOPUPMANAGER_H

#include <QList>
#include <QPoint>
#include <QSize>

class QWidget;

namespace qel {

enum class PopupPlacement {
    Bottom,
    Top,
    Left,
    Right
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
    static QPoint computePopupPosition(QWidget *anchor, QSize popupSize, PopupPlacement placement);
    static int acquireZIndex(PopupType type);
    static void registerPopup(QWidget *popup, PopupPolicy policy = PopupPolicy());
    static void closeAll(PopupType type);
    static void handleScreenBoundary(QWidget *popup);

private:
    struct PopupRecord {
        QWidget *popup = nullptr;
        PopupPolicy policy;
    };

    static QList<PopupRecord> popups_;
    static int zIndexSeed_;
};

} // namespace qel

#endif // QELPOPUPMANAGER_H
