#ifndef QELBUTTON_H
#define QELBUTTON_H

#include <QMap>
#include <QString>
#include <QWidget>
#include <QVariant>
#include <QPushButton>

// get value from https://element-plus.gitee.io/#/en-US/component/color
#define PRIMARY_COLOR #409EFF
#define SUCCESS_COLOR #67C23A
#define INFO_COLOR    #909399
#define WARNING_COLOR #E6A23C
#define DANGER_COLOR  #F56C6C
#define DEFAULT_COLOR #FFFFFF

#define DEFAULT_HOVER_COLOR #ECF5FF
#define PRIMARY_HOVER_COLOR #66B1FF
#define SUCCESS_HOVER_COLOR #85CE61
#define INFO_HOVER_COLOR    #A6A9AD
#define WARNING_HOVER_COLOR #EBB563
#define DANGER_HOVER_COLOR  #F78989

#define PRIMARY_PLAIN_COLOR #3A8EE6
#define SUCCESS_PLAIN_COLOR #5DAF34
#define INFO_PLAIN_COLOR    #82848A
#define WARNING_PLAIN_COLOR #CF9236
#define DANGER_PLAIN_COLOR  #DD6161
#
#define PRIMARY_TEXT_COLOR     #303133
#define REGULAR_TEXT_COLOR     #606266
#define SECONDARY_TEXT_COLOR   #909399
#define PLACEHORDER_TEXT_COLOR #C0C4CC

#define BASE_BORDER_COLOR           #DCDFE6
#define LIGHT_BORDER_COLOR          #E4E7ED
#define LIGHTER_BORDER_COLOR        #EBEEF5
#define EXTRA_LIGHT_BORDER_COLOR    #F2F6FC

#define STR(R)          #R
#define MACRO_STR(R)    STR(R)

namespace qel
{

enum class ButtonSize {
    Medium = 0,
    Small  = 1,
    Mini   = 2
};

enum class ButtonType {
    Default = 0,
    Primary = 1,
    Success = 2,
    Warning = 3,
    Danger  = 4,
    Info    = 5,
    Text    = 6
};

typedef struct ButtonColor_ {
    QString normal_color;
    QString hover_color;
    QString plain_color;
} ButtonColor;

const int SizeMedium = 0x1;
const int SizeSmall  = 0x2;
const int SizeMini   = 0x4;

const int TypePrimary = 0x10;
const int TypeSuccess = 0x20;
const int TypeWarning = 0x40;
const int TypeDanger  = 0x80;
const int TypeInfo    = 0x100;
const int TypeText    = 0x200;

const int Plain    = 0x1000;
const int Round    = 0x2000;
const int Circle   = 0x4000;
const int Loading  = 0x8000;
const int Disabled = 0x10000;

class QelButton : public QPushButton
{
    Q_OBJECT

public:
    QelButton(QWidget *parent = 0,
              QString    text    = "",
              ButtonSize btnSize = ButtonSize::Medium,
              ButtonType btnType = ButtonType::Default,
              bool isPlain = false,
              bool isRound = false,
              bool isCircle = false,
              bool isDisabled = false,
              bool isLoading = false
              );
    ~QelButton();


public:


private:
    ButtonSize getSize();
    ButtonType getType();
    void updateStyle();

private:
    QString    btn_text_;
    ButtonSize btn_size_;
    ButtonType btn_type_;
    bool       is_plain_    = false;
    bool       is_round_    = false;
    bool       is_circle_   = false;
    bool       is_loading_  = false;
    bool       is_disabled_ = false;

    QMap<ButtonType, ButtonColor> btn_colors_ = {
        {ButtonType::Default,   {"#FFFFFF", "#ECF5FF", "#FFFFFF"}},
        {ButtonType::Primary,   {"#409EFF", "#66B1FF", "#3A8EE6"}},
        {ButtonType::Success,   {"#67C23A", "#85CE61", "#5DAF34"}},
        {ButtonType::Info,      {"#909399", "#A6A9AD", "#82848A"}},
        {ButtonType::Warning,      {"#909399", "#A6A9AD", "#82848A"}},

    };
    QMap<ButtonType, QString> hover_color_;
    QMap<ButtonType, QString> plain_color_;
    QVariantMap options_;
    QMap<QString, ButtonSize> map_size_str_;
    QMap<ButtonSize, QSize>   map_size_;

};

} // namespace qel


#endif // QELBUTTON_H
