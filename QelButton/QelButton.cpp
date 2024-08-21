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
    QString textColor = "white";
    QString hoverTextColor = textColor;
    QString borderColor;
    QString hoverBorderColor;

    switch (type_) {
    case Primary:
        backgroundColor = "#409EFF";
        hoverBackgroundColor = "#66B1FF";
        borderColor = "#409EFF";
        hoverBorderColor = "#66B1FF";
        break;
    case Success:
        backgroundColor = "#67C23A";
        hoverBackgroundColor = "#85CE61";
        borderColor = "#67C23A";
        hoverBorderColor = "#85CE61";
        break;
    case Warning:
        backgroundColor = "#E6A23C";
        hoverBackgroundColor = "#EBB563";
        borderColor = "#E6A23C";
        hoverBorderColor = "#EBB563";
        break;
    case Danger:
        backgroundColor = "#F56C6C";
        hoverBackgroundColor = "#F78989";
        borderColor = "#F56C6C";
        hoverBorderColor = "#F78989";
        break;
    case Info:
        backgroundColor = "#909399";
        hoverBackgroundColor = "#A6A9AD";
        borderColor = "#909399";
        hoverBorderColor = "#A6A9AD";
        break;
    default:
        backgroundColor = "#ffffff";
        hoverBackgroundColor = "#ECF5FF";
        textColor = "black";
        hoverTextColor = "#000000";
        borderColor = "#dcdfe6";
        hoverBorderColor = "#ECF5FF";
        break;
    }

    if (isPlain_) {
        textColor = backgroundColor;
        hoverTextColor = hoverBackgroundColor;
        backgroundColor = "transparent";
        hoverBackgroundColor = "transparent";
    }

            // 设置按钮默认样式
    style += QString("QPushButton { background-color: %1; color: %2; border: 1px solid %3;")
                 .arg(backgroundColor)
                 .arg(textColor)
                 .arg(borderColor);

    QString hoverStyle = QString("QPushButton:hover { background-color: %1; color: %2; border: 1px solid %3; }")
                             .arg(hoverBackgroundColor)
                             .arg(hoverTextColor)
                             .arg(hoverBorderColor);

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

    style += hoverStyle; // 添加 hover 样式

            // 设置样式表
    this->setStyleSheet(style);
}


}   // namespace qel
