#ifndef QELTHEME_H
#define QELTHEME_H

#include <QString>

namespace qel {

class QelTheme {
public:
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
