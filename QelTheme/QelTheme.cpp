#include "QelTheme.h"

namespace qel {

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
    return {
        {"#FFFFFF", "#606266", "#DCDFE6"},
        {"#ECF5FF", "#606266", "#DCDFE6"},
        {"#EBEEF5", "#C0C4CC", "#E4E7ED"}
    };
}

QelTheme::ButtonColors QelTheme::primaryButtonColors(bool isPlain)
{
    if (isPlain) {
        return {
            {"#ECF5FF", "#409EFF", "#409EFF"},
            {"#D9ECFF", "#409EFF", "#66B1FF"},
            {"#F3F8FF", "#A0CFFF", "#D6E4FF"}
        };
    }

    return {
        {"#409EFF", "#FFFFFF", "#409EFF"},
        {"#66B1FF", "#FFFFFF", "#66B1FF"},
        {"#B3D8FF", "#FFFFFF", "#B3D8FF"}
    };
}

QelTheme::ButtonColors QelTheme::successButtonColors(bool isPlain)
{
    if (isPlain) {
        return {
            {"#F0F9EB", "#67C23A", "#67C23A"},
            {"#E1F3D8", "#67C23A", "#85CE61"},
            {"#F4F7EF", "#B2E7A9", "#E1EFE3"}
        };
    }

    return {
        {"#67C23A", "#FFFFFF", "#67C23A"},
        {"#85CE61", "#FFFFFF", "#85CE61"},
        {"#B3E19D", "#FFFFFF", "#B3E19D"}
    };
}

QelTheme::ButtonColors QelTheme::warningButtonColors(bool isPlain)
{
    if (isPlain) {
        return {
            {"#FDF6EC", "#E6A23C", "#E6A23C"},
            {"#FAECD8", "#E6A23C", "#EBB563"},
            {"#FEF2E5", "#F1D09C", "#FCE7CE"}
        };
    }

    return {
        {"#E6A23C", "#FFFFFF", "#E6A23C"},
        {"#EBB563", "#FFFFFF", "#EBB563"},
        {"#F3D19E", "#FFFFFF", "#F3D19E"}
    };
}

QelTheme::ButtonColors QelTheme::dangerButtonColors(bool isPlain)
{
    if (isPlain) {
        return {
            {"#FEF0F0", "#F56C6C", "#F56C6C"},
            {"#FDE2E2", "#F56C6C", "#F78989"},
            {"#FEF2F2", "#F9B0B0", "#FDE2E2"}
        };
    }

    return {
        {"#F56C6C", "#FFFFFF", "#F56C6C"},
        {"#F78989", "#FFFFFF", "#F78989"},
        {"#FAB6B6", "#FFFFFF", "#FAB6B6"}
    };
}

QelTheme::ButtonColors QelTheme::infoButtonColors(bool isPlain)
{
    if (isPlain) {
        return {
            {"#F4F4F5", "#909399", "#909399"},
            {"#EBEBEC", "#909399", "#A6A9AD"},
            {"#F6F6F7", "#C8C9CC", "#ECECEE"}
        };
    }

    return {
        {"#909399", "#FFFFFF", "#909399"},
        {"#A6A9AD", "#FFFFFF", "#A6A9AD"},
        {"#C8C9CC", "#FFFFFF", "#C8C9CC"}
    };
}

QelTheme::ButtonColors QelTheme::textButtonColors(bool)
{
    return {
        {"transparent", "#409EFF", "transparent"},
        {"transparent", "#66B1FF", "transparent"},
        {"transparent", "#A0CFFF", "transparent"}
    };
}

} // namespace qel
