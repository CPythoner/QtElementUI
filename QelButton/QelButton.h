#ifndef QELBUTTON_H
#define QELBUTTON_H

#include <QMap>
#include <QString>
#include <QWidget>
#include <QVariant>
#include <QPushButton>

#include "../QelCommon/QelControlTypes.h"

// get value from https://element-plus.gitee.io/#/en-US/component/color
#define PRIMARY_COLOR "409EFF"
#define SUCCESS_COLOR "67C23A"
#define INFO_COLOR    "909399"
#define WARNING_COLOR "E6A23C"
#define DANGER_COLOR  "F56C6C"
#define DEFAULT_COLOR "FFFFFF"

#define DEFAULT_HOVER_COLOR "#ECF5FF"
#define PRIMARY_HOVER_COLOR "#66B1FF"
#define SUCCESS_HOVER_COLOR "#85CE61"
#define INFO_HOVER_COLOR    "#A6A9AD"
#define WARNING_HOVER_COLOR "#EBB563"
#define DANGER_HOVER_COLOR  "#F78989"

#define PRIMARY_PLAIN_COLOR "3A8EE6"
#define SUCCESS_PLAIN_COLOR "5DAF34"
#define INFO_PLAIN_COLOR    "82848A"
#define WARNING_PLAIN_COLOR "CF9236"
#define DANGER_PLAIN_COLOR  "DD6161"
#
#define PRIMARY_TEXT_COLOR     "303133"
#define REGULAR_TEXT_COLOR     "606266"
#define SECONDARY_TEXT_COLOR   "909399"
#define PLACEHORDER_TEXT_COLOR "C0C4CC"

#define BASE_BORDER_COLOR           "DCDFE6"
#define LIGHT_BORDER_COLOR          "E4E7ED"
#define LIGHTER_BORDER_COLOR        "EBEEF5"
#define EXTRA_LIGHT_BORDER_COLOR    "F2F6FC"

#define STR(R)          #R
#define MACRO_STR(R)    STR(R)

namespace qel
{

class QelButton : public QPushButton {
    Q_OBJECT

public:
    using ButtonType = QelButtonType;
    using ButtonSize = QelControlSize;
    using NativeButtonType = QelNativeButtonType;

    static constexpr ButtonType Default = ButtonType::Default;
    static constexpr ButtonType Primary = ButtonType::Primary;
    static constexpr ButtonType Success = ButtonType::Success;
    static constexpr ButtonType Warning = ButtonType::Warning;
    static constexpr ButtonType Danger = ButtonType::Danger;
    static constexpr ButtonType Info = ButtonType::Info;
    static constexpr ButtonType Text = ButtonType::Text;

    static constexpr ButtonSize Large = ButtonSize::Large;
    static constexpr ButtonSize Medium = ButtonSize::Medium;
    static constexpr ButtonSize Small = ButtonSize::Small;
    static constexpr ButtonSize Mini = ButtonSize::Mini;

    static constexpr NativeButtonType Button = NativeButtonType::Button;
    static constexpr NativeButtonType Submit = NativeButtonType::Submit;
    static constexpr NativeButtonType Reset = NativeButtonType::Reset;

            // 构造函数带参数
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

            // Getter 和 Setter
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

private:
    ButtonType type_;
    ButtonSize size_;
    bool isPlain_;
    bool isRound_;
    bool isCircle_;
    bool isLoading_;
    NativeButtonType nativeType_;

    void updateButtonStyle();
};

} // namespace qel


#endif // QELBUTTON_H
