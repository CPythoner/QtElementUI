#include "QelTheme.h"

namespace qel {

const QelTheme::ColorTokens &QelTheme::colors()
{
    static const ColorTokens tokens = {
        "#409EFF",
        "#66B1FF",
        "#ECF5FF",
        "#A0CFFF",

        "#67C23A",
        "#85CE61",
        "#E6A23C",
        "#EBB563",
        "#F56C6C",
        "#F78989",
        "#909399",
        "#A6A9AD",

        "#303133",
        "#606266",
        "#909399",
        "#C0C4CC",

        "#DCDFE6",
        "#E4E7ED",
        "#EBEEF5",

        "#FFFFFF",
        "#F5F7FA",
        "#FAFAFA",
        "#E6E9EF"
    };

    return tokens;
}

QelTheme::ButtonColors QelTheme::buttonColors(ButtonKind kind, bool isPlain)
{
    switch (kind) {
    case ButtonKind::Primary:
        return primaryButtonColors(isPlain);
    case ButtonKind::Success:
        return successButtonColors(isPlain);
    case ButtonKind::Warning:
        return warningButtonColors(isPlain);
    case ButtonKind::Danger:
        return dangerButtonColors(isPlain);
    case ButtonKind::Info:
        return infoButtonColors(isPlain);
    case ButtonKind::Text:
        return textButtonColors(isPlain);
    case ButtonKind::Default:
    default:
        return defaultButtonColors(isPlain);
    }
}

QelTheme::ButtonColors QelTheme::defaultButtonColors(bool)
{
    const ColorTokens &c = colors();
    return {
        {c.fillBlank, c.textRegular, c.borderBase},
        {c.primaryLight, c.textRegular, c.borderBase},
        {c.borderLighter, c.textPlaceholder, c.borderLight}
    };
}

QelTheme::ButtonColors QelTheme::primaryButtonColors(bool isPlain)
{
    const ColorTokens &c = colors();
    if (isPlain) {
        return {
            {c.primaryLight, c.primary, c.primary},
            {"#D9ECFF", c.primary, c.primaryHover},
            {"#F3F8FF", c.primaryDisabled, "#D6E4FF"}
        };
    }

    return {
        {c.primary, c.fillBlank, c.primary},
        {c.primaryHover, c.fillBlank, c.primaryHover},
        {"#B3D8FF", c.fillBlank, "#B3D8FF"}
    };
}

QelTheme::ButtonColors QelTheme::successButtonColors(bool isPlain)
{
    const ColorTokens &c = colors();
    if (isPlain) {
        return {
            {"#F0F9EB", c.success, c.success},
            {"#E1F3D8", c.success, c.successHover},
            {"#F4F7EF", "#B2E7A9", "#E1EFE3"}
        };
    }

    return {
        {c.success, c.fillBlank, c.success},
        {c.successHover, c.fillBlank, c.successHover},
        {"#B3E19D", c.fillBlank, "#B3E19D"}
    };
}

QelTheme::ButtonColors QelTheme::warningButtonColors(bool isPlain)
{
    const ColorTokens &c = colors();
    if (isPlain) {
        return {
            {"#FDF6EC", c.warning, c.warning},
            {"#FAECD8", c.warning, c.warningHover},
            {"#FEF2E5", "#F1D09C", "#FCE7CE"}
        };
    }

    return {
        {c.warning, c.fillBlank, c.warning},
        {c.warningHover, c.fillBlank, c.warningHover},
        {"#F3D19E", c.fillBlank, "#F3D19E"}
    };
}

QelTheme::ButtonColors QelTheme::dangerButtonColors(bool isPlain)
{
    const ColorTokens &c = colors();
    if (isPlain) {
        return {
            {"#FEF0F0", c.danger, c.danger},
            {"#FDE2E2", c.danger, c.dangerHover},
            {"#FEF2F2", "#F9B0B0", "#FDE2E2"}
        };
    }

    return {
        {c.danger, c.fillBlank, c.danger},
        {c.dangerHover, c.fillBlank, c.dangerHover},
        {"#FAB6B6", c.fillBlank, "#FAB6B6"}
    };
}

QelTheme::ButtonColors QelTheme::infoButtonColors(bool isPlain)
{
    const ColorTokens &c = colors();
    if (isPlain) {
        return {
            {"#F4F4F5", c.info, c.info},
            {"#EBEBEC", c.info, c.infoHover},
            {"#F6F6F7", "#C8C9CC", "#ECECEE"}
        };
    }

    return {
        {c.info, c.fillBlank, c.info},
        {c.infoHover, c.fillBlank, c.infoHover},
        {"#C8C9CC", c.fillBlank, "#C8C9CC"}
    };
}

QelTheme::ButtonColors QelTheme::textButtonColors(bool)
{
    const ColorTokens &c = colors();
    return {
        {"transparent", c.primary, "transparent"},
        {"transparent", c.primaryHover, "transparent"},
        {"transparent", c.primaryDisabled, "transparent"}
    };
}

} // namespace qel
