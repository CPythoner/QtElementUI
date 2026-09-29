#ifndef QELTHEME_H
#define QELTHEME_H

#include <QString>

namespace qel {

class QelTheme {
public:
    struct ColorTokens {
        QString primary;
        QString primaryHover;
        QString primaryLight;
        QString primaryDisabled;

        QString success;
        QString successHover;
        QString warning;
        QString warningHover;
        QString danger;
        QString dangerHover;
        QString info;
        QString infoHover;

        QString textPrimary;
        QString textRegular;
        QString textSecondary;
        QString textPlaceholder;

        QString borderBase;
        QString borderLight;
        QString borderLighter;

        QString fillBlank;
        QString fillLight;
        QString fillLighter;
        QString fillPressed;
    };

    struct ButtonStateColors {
        QString background;
        QString text;
        QString border;
    };

    struct ButtonColors {
        ButtonStateColors normal;
        ButtonStateColors hover;
        ButtonStateColors disabled;
    };

    enum class ButtonKind {
        Default,
        Primary,
        Success,
        Warning,
        Danger,
        Info,
        Text
    };

    static const ColorTokens &colors();
    static ButtonColors buttonColors(ButtonKind kind, bool isPlain);

private:
    static ButtonColors defaultButtonColors(bool isPlain);
    static ButtonColors primaryButtonColors(bool isPlain);
    static ButtonColors successButtonColors(bool isPlain);
    static ButtonColors warningButtonColors(bool isPlain);
    static ButtonColors dangerButtonColors(bool isPlain);
    static ButtonColors infoButtonColors(bool isPlain);
    static ButtonColors textButtonColors(bool isPlain);
};

} // namespace qel

#endif // QELTHEME_H
