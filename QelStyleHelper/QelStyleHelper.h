#ifndef QELSTYLEHELPER_H
#define QELSTYLEHELPER_H

#include <QString>

#include "../QelTheme/QelTheme.h"

namespace qel {

enum class QelVisualState {
    Normal,
    Hover,
    Active,
    Focus,
    Disabled,
    Loading
};

struct QelStateContext {
    bool enabled = true;
    bool loading = false;
    bool hovered = false;
    bool pressed = false;
    bool focused = false;
};

class QelStyleHelper {
public:
    struct ButtonStyle {
        QString background;
        QString text;
        QString border;
    };

    static QelVisualState resolveState(const QelStateContext &ctx);
    static ButtonStyle buttonStyle(QelTheme::ButtonKind kind, bool isPlain, QelVisualState state);
};

} // namespace qel

#endif // QELSTYLEHELPER_H
