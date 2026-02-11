#include "QelButton.h"
#include "../QelTheme/QelTheme.h"
#include "../QelStyleHelper/QelStyleHelper.h"

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
    setEnabled(!isLoading_);
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

    QelTheme::ButtonKind kind = QelTheme::ButtonKind::Default;
    switch (type_) {
    case Primary:
        kind = QelTheme::ButtonKind::Primary;
        break;
    case Success:
        kind = QelTheme::ButtonKind::Success;
        break;
    case Warning:
        kind = QelTheme::ButtonKind::Warning;
        break;
    case Danger:
        kind = QelTheme::ButtonKind::Danger;
        break;
    case Info:
        kind = QelTheme::ButtonKind::Info;
        break;
    case Text:
        kind = QelTheme::ButtonKind::Text;
        break;
    case Default:
    default:
        kind = QelTheme::ButtonKind::Default;
        break;
    }

    const QelStyleHelper::ButtonStyle normalStyle =
        QelStyleHelper::buttonStyle(kind, isPlain_, QelVisualState::Normal);
    const QelStyleHelper::ButtonStyle hoverStyleToken =
        QelStyleHelper::buttonStyle(kind, isPlain_, QelVisualState::Hover);
    const QelStyleHelper::ButtonStyle activeStyleToken =
        QelStyleHelper::buttonStyle(kind, isPlain_, QelVisualState::Active);
    const QelStyleHelper::ButtonStyle disabledStyleToken =
        QelStyleHelper::buttonStyle(kind, isPlain_, QelVisualState::Disabled);

    style += QString("QPushButton { background-color: %1; color: %2; border: 1px solid %3;")
                 .arg(normalStyle.background)
                 .arg(normalStyle.text)
                 .arg(normalStyle.border);

    QString hoverStyle = QString("QPushButton:hover { background-color: %1; color: %2; border: 1px solid %3; }")
                             .arg(hoverStyleToken.background)
                             .arg(hoverStyleToken.text)
                             .arg(hoverStyleToken.border);

    QString activeStyle = QString("QPushButton:pressed { background-color: %1; color: %2; border: 1px solid %3; }")
                              .arg(activeStyleToken.background)
                              .arg(activeStyleToken.text)
                              .arg(activeStyleToken.border);

    QString disabledStyle = QString("QPushButton:disabled { background-color: %1; color: %2; border: 1px solid %3; }")
                                .arg(disabledStyleToken.background)
                                .arg(disabledStyleToken.text)
                                .arg(disabledStyleToken.border);

    switch (size_) {
    case Large: style += " font-size: 16px; padding: 10px 20px;"; break;
    case Medium: style += " font-size: 14px; padding: 8px 16px;"; break;
    case Small: style += " font-size: 12px; padding: 6px 12px;"; break;
    case Mini: style += " font-size: 10px; padding: 4px 8px;"; break;
    }

    QString roundQSS;

    if (isRound_) {
        roundQSS = QString(" border-radius: %1px;").arg(this->height()/2);
    } else {
        roundQSS = " border-radius: 4px;";
    }

    if (isCircle_) {
        roundQSS = QString(" border-radius: %1px;").arg(this->height()/2);
        setFixedWidth(this->height());
    }

    style += roundQSS + " }";
    style += hoverStyle;
    style += activeStyle;
    style += disabledStyle;

    this->setStyleSheet(style);
}



}   // namespace qel
