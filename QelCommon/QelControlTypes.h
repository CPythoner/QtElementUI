#ifndef QELCONTROLTYPES_H
#define QELCONTROLTYPES_H

namespace qel {

enum class QelControlSize {
    Large,
    Medium,
    Small,
    Mini
};

// Semantic color type shared by multiple controls (not Button-specific).
enum class QelSemanticType {
    Default,
    Primary,
    Success,
    Warning,
    Danger,
    Info
};

enum class QelButtonVisualType {
    Filled,
    Text,
    Link
};

using QelButtonType = QelSemanticType;

enum class QelNativeButtonType {
    Button,
    Submit,
    Reset
};

} // namespace qel

#endif // QELCONTROLTYPES_H
