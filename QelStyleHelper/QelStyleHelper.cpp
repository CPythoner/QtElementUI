#include "QelStyleHelper.h"

namespace qel {

QelVisualState QelStyleHelper::resolveState(const QelStateContext &ctx)
{
    if (!ctx.enabled) {
        return QelVisualState::Disabled;
    }

    if (ctx.loading) {
        return QelVisualState::Loading;
    }

    if (ctx.pressed) {
        return QelVisualState::Active;
    }

    if (ctx.hovered) {
        return QelVisualState::Hover;
    }

    if (ctx.focused) {
        return QelVisualState::Focus;
    }

    return QelVisualState::Normal;
}

QelStyleHelper::ButtonStyle QelStyleHelper::buttonStyle(QelTheme::ButtonKind kind,
                                                        bool isPlain,
                                                        QelVisualState state)
{
    const QelTheme::ButtonColors colors = QelTheme::buttonColors(kind, isPlain);

    switch (state) {
    case QelVisualState::Disabled:
    case QelVisualState::Loading:
        return {colors.disabled.background, colors.disabled.text, colors.disabled.border};
    case QelVisualState::Active:
        return {colors.hover.background, colors.hover.text, colors.hover.border};
    case QelVisualState::Hover:
        return {colors.hover.background, colors.hover.text, colors.hover.border};
    case QelVisualState::Focus:
    case QelVisualState::Normal:
    default:
        return {colors.normal.background, colors.normal.text, colors.normal.border};
    }
}

} // namespace qel
