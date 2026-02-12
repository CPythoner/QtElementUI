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

QelStyleHelper::ComponentStyle QelStyleHelper::buttonStyle(QelTheme::ButtonKind kind,
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

QelStyleHelper::StateStyleSet QelStyleHelper::buttonStateStyles(QelTheme::ButtonKind kind, bool isPlain)
{
    return {
        buttonStyle(kind, isPlain, QelVisualState::Normal),
        buttonStyle(kind, isPlain, QelVisualState::Hover),
        buttonStyle(kind, isPlain, QelVisualState::Active),
        buttonStyle(kind, isPlain, QelVisualState::Focus),
        buttonStyle(kind, isPlain, QelVisualState::Disabled),
        buttonStyle(kind, isPlain, QelVisualState::Loading)
    };
}

QString QelStyleHelper::composeStateStyleSheet(const QString &baseSelector,
                                               const QString &loadingSelector,
                                               const StateStyleSet &styles,
                                               bool disableFocusOutline)
{
    QString style;
    style += QString("%1 { background-color: %2; color: %3; border: 1px solid %4; }")
                 .arg(baseSelector)
                 .arg(styles.normal.background)
                 .arg(styles.normal.text)
                 .arg(styles.normal.border);

    style += QString("%1:hover { background-color: %2; color: %3; border: 1px solid %4; }")
                 .arg(baseSelector)
                 .arg(styles.hover.background)
                 .arg(styles.hover.text)
                 .arg(styles.hover.border);

    style += QString("%1:pressed { background-color: %2; color: %3; border: 1px solid %4; }")
                 .arg(baseSelector)
                 .arg(styles.active.background)
                 .arg(styles.active.text)
                 .arg(styles.active.border);

    style += QString("%1:focus { background-color: %2; color: %3; border: 1px solid %4;%5 }")
                 .arg(baseSelector)
                 .arg(styles.focus.background)
                 .arg(styles.focus.text)
                 .arg(styles.focus.border)
                 .arg(disableFocusOutline ? " outline: none;" : "");

    style += QString("%1:disabled { background-color: %2; color: %3; border: 1px solid %4; }")
                 .arg(baseSelector)
                 .arg(styles.disabled.background)
                 .arg(styles.disabled.text)
                 .arg(styles.disabled.border);

    style += QString("%1 { background-color: %2; color: %3; border: 1px solid %4; }")
                 .arg(loadingSelector)
                 .arg(styles.loading.background)
                 .arg(styles.loading.text)
                 .arg(styles.loading.border);

    return style;
}

QString QelStyleHelper::buttonStateStyleSheet(QelTheme::ButtonKind kind, bool isPlain)
{
    const StateStyleSet styles = buttonStateStyles(kind, isPlain);
    return composeStateStyleSheet("QPushButton", "QPushButton[qel-loading=\"true\"]", styles, true);
}

} // namespace qel
