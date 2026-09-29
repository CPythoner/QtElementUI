#include "QelButton.h"

#include <QColor>
#include <QVariant>

#include "../QelStyleHelper/QelStyleHelper.h"
#include "../QelTheme/QelTheme.h"

namespace qel
{

namespace {

QelTheme::ButtonKind toButtonKind(QelButton::ButtonType type)
{
    switch (type) {
    case QelButton::ButtonType::Primary:
        return QelTheme::ButtonKind::Primary;
    case QelButton::ButtonType::Success:
        return QelTheme::ButtonKind::Success;
    case QelButton::ButtonType::Warning:
        return QelTheme::ButtonKind::Warning;
    case QelButton::ButtonType::Danger:
        return QelTheme::ButtonKind::Danger;
    case QelButton::ButtonType::Info:
        return QelTheme::ButtonKind::Info;
    case QelButton::ButtonType::Default:
    default:
        return QelTheme::ButtonKind::Default;
    }
}

QColor semanticColor(QelButton::ButtonType type)
{
    const QelTheme::ColorTokens &c = QelTheme::colors();

    switch (type) {
    case QelButton::ButtonType::Primary:
        return QColor(c.primary);
    case QelButton::ButtonType::Success:
        return QColor(c.success);
    case QelButton::ButtonType::Warning:
        return QColor(c.warning);
    case QelButton::ButtonType::Danger:
        return QColor(c.danger);
    case QelButton::ButtonType::Info:
        return QColor(c.info);
    case QelButton::ButtonType::Default:
    default:
        return QColor(c.textRegular);
    }
}

QColor parseColorOrDefault(const QString &input, const QColor &fallback)
{
    const QColor fromInput(input);
    if (fromInput.isValid()) {
        return fromInput;
    }

    return fallback;
}

void applyCustomColor(QelStyleHelper::StateStyleSet &styles, const QString &color)
{
    const QelTheme::ColorTokens &c = QelTheme::colors();
    const QColor base = parseColorOrDefault(color, QColor(c.primary));
    const QColor hover = base.lighter(110);
    const QColor disabled = base.lighter(138);

    styles.normal.background = base.name();
    styles.normal.border = base.name();
    styles.normal.text = c.fillBlank;

    styles.hover.background = hover.name();
    styles.hover.border = hover.name();
    styles.hover.text = c.fillBlank;

    styles.active = styles.hover;
    styles.focus = styles.hover;

    styles.disabled.background = disabled.name();
    styles.disabled.border = disabled.name();
    styles.disabled.text = c.fillBlank;

    styles.loading = styles.disabled;
}

void applyTextLikeStyle(QelStyleHelper::StateStyleSet &styles,
                        QelButton::ButtonType type,
                        bool isLink,
                        bool hasBackground)
{
    const QelTheme::ColorTokens &c = QelTheme::colors();
    const QColor semantic = semanticColor(type);
    const QString normalText = semantic.name();
    const QString hoverText = semantic.lighter(115).name();
    const QString disabledText = semantic.lighter(150).name();

    styles.normal.background = hasBackground ? c.fillLight : "transparent";
    styles.normal.border = "transparent";
    styles.normal.text = normalText;

    styles.hover.background = hasBackground ? c.borderLight : c.primaryLight;
    styles.hover.border = "transparent";
    styles.hover.text = hoverText;

    styles.active = styles.hover;
    styles.focus = styles.hover;

    styles.disabled.background = hasBackground ? c.fillLight : "transparent";
    styles.disabled.border = "transparent";
    styles.disabled.text = disabledText;

    styles.loading = styles.disabled;

    if (isLink) {
        styles.hover.background = "transparent";
        styles.focus.background = "transparent";
    }
}

} // namespace

QelButton::QelButton(ButtonType type,
                     ButtonSize size,
                     bool isPlain,
                     bool isRound,
                     bool isCircle,
                     bool isLoading,
                     NativeButtonType nativeType,
                     const QIcon &icon,
                     const QString &text,
                     QWidget *parent)
    : QPushButton(text, parent)
    , type_(type)
    , size_(size)
    , isPlain_(isPlain)
    , isRound_(isRound)
    , isCircle_(isCircle)
    , isLoading_(isLoading)
    , nativeType_(nativeType)
{
    setIcon(icon);
    setProperty("qel-loading", isLoading_);
    setEnabled(!isLoading_);
    setCursor(Qt::PointingHandCursor);
    updateButtonStyle();
}

void QelButton::setType(ButtonType type) {
    type_ = type;
    updateButtonStyle();
}

void QelButton::setSize(ButtonSize size) {
    size_ = size;
    updateButtonStyle();
}

void QelButton::setPlain(bool isPlain) {
    isPlain_ = isPlain;
    updateButtonStyle();
}

void QelButton::setRound(bool isRound) {
    isRound_ = isRound;
    updateButtonStyle();
}

void QelButton::setCircle(bool isCircle) {
    isCircle_ = isCircle;
    updateButtonStyle();
}

void QelButton::setLoading(bool isLoading) {
    isLoading_ = isLoading;
    setEnabled(!isLoading_);
    setProperty("qel-loading", isLoading_);
    updateButtonStyle();
}

void QelButton::setDisabled(bool isDisabled) {
    setEnabled(!isDisabled);
    updateButtonStyle();
}

void QelButton::setIcon(const QIcon &icon) {
    QPushButton::setIcon(icon);
}

void QelButton::setAutofocus(bool autofocus) {
    setFocusPolicy(autofocus ? Qt::StrongFocus : Qt::NoFocus);
}

void QelButton::setNativeType(NativeButtonType nativeType) {
    nativeType_ = nativeType;
    if (nativeType == NativeButtonType::Submit) {
        setProperty("type", "submit");
    } else if (nativeType == NativeButtonType::Reset) {
        setProperty("type", "reset");
    } else {
        setProperty("type", "button");
    }
}

void QelButton::setVisualType(VisualType visualType)
{
    visualType_ = visualType;
    updateButtonStyle();
}

void QelButton::setTextMode(bool isTextMode)
{
    visualType_ = isTextMode ? VisualType::Text : VisualType::Filled;
    updateButtonStyle();
}

void QelButton::setLinkMode(bool isLinkMode)
{
    visualType_ = isLinkMode ? VisualType::Link : VisualType::Filled;
    updateButtonStyle();
}

void QelButton::setBg(bool hasBackground)
{
    hasBackground_ = hasBackground;
    updateButtonStyle();
}

void QelButton::setColor(const QString &color)
{
    customColor_ = color;
    updateButtonStyle();
}

void QelButton::setDark(bool dark)
{
    dark_ = dark;
    Q_UNUSED(dark_);
    updateButtonStyle();
}

void QelButton::updateButtonStyle()
{
    QString style;

    const QelTheme::ButtonKind kind = toButtonKind(type_);
    QelStyleHelper::StateStyleSet styles =
        QelStyleHelper::buttonStateStyles(kind, isPlain_);

    if (!customColor_.isEmpty()) {
        applyCustomColor(styles, customColor_);
    }

    if (visualType_ == VisualType::Text || visualType_ == VisualType::Link) {
        applyTextLikeStyle(
            styles,
            type_,
            visualType_ == VisualType::Link,
            hasBackground_);
    }

    style += QelStyleHelper::composeStateStyleSheet(
        "QPushButton",
        "QPushButton[qel-loading=\"true\"]",
        styles,
        true);

    QString sizeStyle;
    switch (size_) {
    case ButtonSize::Large:
        sizeStyle = "font-size: 16px; padding: 10px 20px;";
        break;
    case ButtonSize::Default:
        sizeStyle = "font-size: 14px; padding: 8px 16px;";
        break;
    case ButtonSize::Small:
        sizeStyle = "font-size: 13px; padding: 6px 12px;";
        break;
    }

    QString roundStyle;
    if (isRound_) {
        roundStyle = QString("border-radius: %1px;").arg(height() / 2);
    } else {
        roundStyle = "border-radius: 4px;";
    }

    if (visualType_ == VisualType::Link) {
        roundStyle = "border-radius: 0px;";
    }

    if (isCircle_) {
        roundStyle = QString("border-radius: %1px;").arg(height() / 2);
        setFixedWidth(height());
    }

    style += QString("QPushButton { %1 %2 }").arg(sizeStyle, roundStyle);

    if (visualType_ == VisualType::Link) {
        style += "QPushButton:hover { text-decoration: underline; }";
    }

    setStyleSheet(style);
}

} // namespace qel
