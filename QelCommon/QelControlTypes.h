#ifndef QELCONTROLTYPES_H
#define QELCONTROLTYPES_H

namespace qel {

enum class QelControlSize {
    Large,
    Medium,
    Small,
    Mini
};

enum class QelButtonType {
    Default,
    Primary,
    Success,
    Warning,
    Danger,
    Info,
    Text
};

enum class QelNativeButtonType {
    Button,
    Submit,
    Reset
};

} // namespace qel

#endif // QELCONTROLTYPES_H
