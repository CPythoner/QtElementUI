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
    struct ComponentStyle {
        QString background;
        QString text;
        QString border;
    };

    struct StateStyleSet {
        ComponentStyle normal;
        ComponentStyle hover;
        ComponentStyle active;
        ComponentStyle focus;
        ComponentStyle disabled;
        ComponentStyle loading;
    };

    static QelVisualState resolveState(const QelStateContext &ctx);
    static ComponentStyle buttonStyle(QelTheme::ButtonKind kind, bool isPlain, QelVisualState state);
    static StateStyleSet buttonStateStyles(QelTheme::ButtonKind kind, bool isPlain);

    static QString composeStateStyleSheet(const QString &baseSelector,
                                          const QString &loadingSelector,
                                          const StateStyleSet &styles,
                                          bool disableFocusOutline = false);

    static QString buttonStateStyleSheet(QelTheme::ButtonKind kind, bool isPlain);
};

} // namespace qel

#endif // QELSTYLEHELPER_H
