#ifndef QELBUTTON_H
#define QELBUTTON_H

#include <QPushButton>
#include <QString>

#include "../QelCommon/QelControlTypes.h"

namespace qel
{

class QelButton : public QPushButton {
    Q_OBJECT

public:
    using ButtonType = QelButtonType;
    using ButtonSize = QelControlSize;
    using NativeButtonType = QelNativeButtonType;
    using VisualType = QelButtonVisualType;

    static constexpr ButtonType Default = ButtonType::Default;
    static constexpr ButtonType Primary = ButtonType::Primary;
    static constexpr ButtonType Success = ButtonType::Success;
    static constexpr ButtonType Warning = ButtonType::Warning;
    static constexpr ButtonType Danger = ButtonType::Danger;
    static constexpr ButtonType Info = ButtonType::Info;

    static constexpr ButtonSize Large = ButtonSize::Large;
    static constexpr ButtonSize Medium = ButtonSize::Medium;
    static constexpr ButtonSize Small = ButtonSize::Small;
    static constexpr ButtonSize Mini = ButtonSize::Mini;

    static constexpr NativeButtonType Button = NativeButtonType::Button;
    static constexpr NativeButtonType Submit = NativeButtonType::Submit;
    static constexpr NativeButtonType Reset = NativeButtonType::Reset;

    static constexpr VisualType Filled = VisualType::Filled;
    static constexpr VisualType Text = VisualType::Text;
    static constexpr VisualType Link = VisualType::Link;

    explicit QelButton(ButtonType type = ButtonType::Default,
                       ButtonSize size = ButtonSize::Medium,
                       bool isPlain = false,
                       bool isRound = false,
                       bool isCircle = false,
                       bool isLoading = false,
                       NativeButtonType nativeType = NativeButtonType::Button,
                       const QIcon &icon = QIcon(),
                       const QString &text = QString(),
                       QWidget *parent = nullptr);

    void setType(ButtonType type);
    void setSize(ButtonSize size);
    void setPlain(bool isPlain);
    void setRound(bool isRound);
    void setCircle(bool isCircle);
    void setLoading(bool isLoading);
    void setDisabled(bool isDisabled);
    void setIcon(const QIcon &icon);
    void setAutofocus(bool autofocus);
    void setNativeType(NativeButtonType nativeType);

    // Element Plus inspired additions.
    void setVisualType(VisualType visualType);
    void setTextMode(bool isTextMode);
    void setLinkMode(bool isLinkMode);
    void setBg(bool hasBackground);
    void setColor(const QString &color);
    void setDark(bool dark);

private:
    ButtonType type_;
    ButtonSize size_;
    bool isPlain_;
    bool isRound_;
    bool isCircle_;
    bool isLoading_;
    NativeButtonType nativeType_;

    VisualType visualType_ = VisualType::Filled;
    bool hasBackground_ = false;
    QString customColor_;
    bool dark_ = false;

    void updateButtonStyle();
};

} // namespace qel

#endif // QELBUTTON_H
