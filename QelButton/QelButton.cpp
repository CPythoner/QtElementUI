#include "QelButton.h"

namespace qel
{

//QelButton::QelButton(QWidget *parent,
//                     QString text,
//                     ButtonSize btnSize,
//                     ButtonType btnType,
//                     bool isPlain,
//                     bool isRound,
//                     bool isCircle,
//                     bool isDisabled,
//                     bool isLoading)
//    : QPushButton(parent),
//      btn_text_(text),
//      btn_size_(btnSize),
//      btn_type_(btnType),
//      is_plain_(isPlain),
//      is_round_(isRound),
//      is_circle_(isCircle),
//      is_loading_(isLoading),
//      is_disabled_(isDisabled)
//{
//    this->updateStyle();
//}

//QelButton::~QelButton()
//{

//}

//ButtonSize QelButton::getSize()
//{

//    return ButtonSize::Medium;
//}

//void QelButton::updateStyle()
//{
//    switch (btn_size_) {
//    case ButtonSize::Medium:
//        this->setFixedSize(98, 36);
//        break;
//    case ButtonSize::Small:
//        this->setFixedSize(80, 32);
//        break;
//    case ButtonSize::Mini:
//        this->setFixedSize(80, 28);
//        break;
//    default:
//        break;
//    }

//    QString type_qss = "";
//    QString hover_qss = "";
//    QString pressed_qss = "";
//    QString type_hover_qss = "";

//    switch (btn_type_)
//    {
//    case qel::ButtonType::Default:
//        type_qss = QString("color:#606266;background-color:%1; border: 1px solid #dcdfe6;").arg(MACRO_STR(DEFAULT_COLOR));
//        type_hover_qss = QString("color:#606266;background-color:%1;").arg(MACRO_STR(DEFAULT_HOVER_COLOR));
//        break;
//        break;
//    case qel::ButtonType::Warning:
//        break;
//    case qel::ButtonType::Danger:
//        break;
//    case qel::ButtonType::Info:
//        break;
//    case qel::ButtonType::Text:
//        break;
//    case ButtonType::Primary:
//        type_qss = QString("color:white;background-color:#%1;").arg(MACRO_STR(PRIMARY_COLOR));
//        type_hover_qss = QString("color:white;background-color:#%1;").arg(MACRO_STR(PRIMARY_HOVER_COLOR));
//        break;
//    case ButtonType::Success:
//        type_qss = QString("color:white;background-color:#%1;").arg(MACRO_STR(SUCCESS_COLOR));
//        type_hover_qss = QString("color:white;background-color:#%1;").arg(MACRO_STR(SUCCESS_HOVER_COLOR));
//        break;
//    default:
//        break;
//    }


//    QString round_qss;
//    if (is_round_)
//        round_qss = QString("border-radius:%1px;").arg(QString::number(this->height()/2));
//    else
//        round_qss = QString("border-radius:4px;");

//    if (is_circle_)
//    {
//        round_qss = QString("border-radius:%1px;").arg(QString::number(this->height()/2));
//        this->setFixedWidth(this->height());
//    }

//    this->setStyleSheet(QString("QPushButton{")
//                        + type_qss
//                        + round_qss
//                        + "}"
//                        + "QPushButton:hover{"
//                        + type_hover_qss
//                        + round_qss
//                        + "}");

//   this->setText(btn_text_);
//}

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
    : QPushButton(text, parent),
    type_(type),
    size_(size),
    isPlain_(isPlain),
    isRound_(isRound),
    isCircle_(isCircle),
    isLoading_(isLoading),
    nativeType_(nativeType)
{
    setIcon(icon);
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
    // 加载状态的图标或样式变更
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
    // 设置为表单按钮类型（submit, reset, button）
    if (nativeType == Submit) {
        setProperty("type", "submit");
    } else if (nativeType == Reset) {
        setProperty("type", "reset");
    } else {
        setProperty("type", "button");
    }
}

void QelButton::updateButtonStyle() {
    QString style;

            // 根据类型设置样式
    QString backgroundColor;
    QString hoverBackgroundColor;
    QString textColor;
    QString hoverTextColor;
    QString borderColor;
    QString hoverBorderColor;
    QString disabledBackgroundColor;
    QString disabledTextColor;
    QString disabledBorderColor;

    switch (type_) {
    case Primary:
        backgroundColor = isPlain_ ? "#ECF5FF" : "#409EFF";
        hoverBackgroundColor = "#66B1FF";
        textColor = isPlain_ ? "#409EFF" : "white";
        hoverTextColor = isPlain_ ? "#409EFF" : "white";
        borderColor = "#409EFF";
        hoverBorderColor = "#66B1FF";
        disabledBackgroundColor = isPlain_ ? "#F3F8FF" : "#B3D8FF";
        disabledTextColor = isPlain_ ? "#A0CFFF" : "white";
        disabledBorderColor = isPlain_ ? "#D6E4FF" : "#B3D8FF";
        break;
    case Success:
        backgroundColor = isPlain_ ? "#F0F9EB" : "#67C23A";
        hoverBackgroundColor = "#85CE61";
        textColor = isPlain_ ? "#67C23A" : "white";
        hoverTextColor = isPlain_ ? "#67C23A" : "white";
        borderColor = "#67C23A";
        hoverBorderColor = "#85CE61";
        disabledBackgroundColor = isPlain_ ? "#F4F7EF" : "#B3E19D";
        disabledTextColor = isPlain_ ? "#B2E7A9" : "white";
        disabledBorderColor = isPlain_ ? "#E1EFE3" : "#B3E19D";
        break;
    case Warning:
        backgroundColor = isPlain_ ? "#FDF6EC" : "#E6A23C";
        hoverBackgroundColor = "#EBB563";
        textColor = isPlain_ ? "#E6A23C" : "white";
        hoverTextColor = isPlain_ ? "#E6A23C" : "white";
        borderColor = "#E6A23C";
        hoverBorderColor = "#EBB563";
        disabledBackgroundColor = isPlain_ ? "#FEF2E5" : "#F3D19E";
        disabledTextColor = isPlain_ ? "#F1D09C" : "white";
        disabledBorderColor = isPlain_ ? "#FCE7CE" : "#F3D19E";
        break;
    case Danger:
        backgroundColor = isPlain_ ? "#FEF0F0" : "#F56C6C";
        hoverBackgroundColor = "#F78989";
        textColor = isPlain_ ? "#F56C6C" : "white";
        hoverTextColor = isPlain_ ? "#F56C6C" : "white";
        borderColor = "#F56C6C";
        hoverBorderColor = "#F78989";
        disabledBackgroundColor = isPlain_ ? "#FEF2F2" : "#FAB6B6";
        disabledTextColor = isPlain_ ? "#F9B0B0" : "white";
        disabledBorderColor = isPlain_ ? "#FDE2E2" : "#FAB6B6";
        break;
    case Info:
        backgroundColor = isPlain_ ? "#F4F4F5" : "#909399";
        hoverBackgroundColor = "#A6A9AD";
        textColor = isPlain_ ? "#909399" : "white";
        hoverTextColor = isPlain_ ? "#909399" : "white";
        borderColor = "#909399";
        hoverBorderColor = "#A6A9AD";
        disabledBackgroundColor = isPlain_ ? "#F6F6F7" : "#C8C9CC";
        disabledTextColor = isPlain_ ? "#C8C9CC" : "white";
        disabledBorderColor = isPlain_ ? "#ECECEE" : "#C8C9CC";
        break;
    default:
        backgroundColor = isPlain_ ? "#ffffff" : "#ffffff";
        hoverBackgroundColor = isPlain_ ? "#ECF5FF" : "#f0f0f0";
        textColor = "#606266";
        hoverTextColor = "#606266";
        borderColor = "#dcdfe6";
        hoverBorderColor = "#dcdfe6";
        disabledBackgroundColor = isPlain_ ? "#F5F7FA" : "#EBEEF5";
        disabledTextColor = "#C0C4CC";
        disabledBorderColor = "#E4E7ED";
        break;
    }

            // 设置按钮默认样式
    style += QString("QPushButton { background-color: %1; color: %2; border: 1px solid %3;")
                 .arg(backgroundColor)
                 .arg(textColor)
                 .arg(borderColor);

            // 设置 hover 样式
    QString hoverStyle = QString("QPushButton:hover { background-color: %1; color: %2; border: 1px solid %3; }")
                             .arg(hoverBackgroundColor)
                             .arg(hoverTextColor)
                             .arg(hoverBorderColor);

            // 设置禁用样式
    QString disabledStyle = QString("QPushButton:disabled { background-color: %1; color: %2; border: 1px solid %3; }")
                                .arg(disabledBackgroundColor)
                                .arg(disabledTextColor)
                                .arg(disabledBorderColor);

            // 设置尺寸
    switch (size_) {
    case Large: style += " font-size: 16px; padding: 10px 20px;"; break;
    case Medium: style += " font-size: 14px; padding: 8px 16px;"; break;
    case Small: style += " font-size: 12px; padding: 6px 12px;"; break;
    case Mini: style += " font-size: 10px; padding: 4px 8px;"; break;
    }

    QString roundQSS;

            // 圆角按钮
    if (isRound_) {
        roundQSS = QString(" border-radius: %1px;").arg(this->height()/2);
    } else {
        roundQSS = " border-radius: 4px;";
    }

            // 圆形按钮
    if (isCircle_) {
        roundQSS = QString(" border-radius: %1px;").arg(this->height()/2);
        setFixedWidth(this->height());
    }

    style += roundQSS + " }"; // 闭合 QPushButton 样式

    style += hoverStyle;  // 添加 hover 样式
    style += disabledStyle;  // 添加禁用状态样式

            // 设置样式表
    this->setStyleSheet(style);
}


}   // namespace qel
