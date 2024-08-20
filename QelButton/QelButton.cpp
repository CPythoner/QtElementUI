#include "QelButton.h"

namespace qel
{

QelButton::QelButton(QWidget *parent,
                     QString text,
                     ButtonSize btnSize,
                     ButtonType btnType,
                     bool isPlain,
                     bool isRound,
                     bool isCircle,
                     bool isDisabled,
                     bool isLoading)
    : QPushButton(parent),
      btn_text_(text),
      btn_size_(btnSize),
      btn_type_(btnType),
      is_plain_(isPlain),
      is_round_(isRound),
      is_circle_(isCircle),
      is_loading_(isLoading),
      is_disabled_(isDisabled)
{
    this->updateStyle();
}

QelButton::~QelButton()
{

}

ButtonSize QelButton::getSize()
{

    return ButtonSize::Medium;
}

void QelButton::updateStyle()
{
    switch (btn_size_) {
    case ButtonSize::Medium:
        this->setFixedSize(98, 36);
        break;
    case ButtonSize::Small:
        this->setFixedSize(80, 32);
        break;
    case ButtonSize::Mini:
        this->setFixedSize(80, 28);
        break;
    default:
        break;
    }

    QString type_qss = "";
    QString hover_qss = "";
    QString pressed_qss = "";
    QString type_hover_qss = "";

    switch (btn_type_)
    {
    case qel::ButtonType::Default:
        type_qss = QString("color:#606266;background-color:%1; border: 1px solid #dcdfe6;").arg(MACRO_STR(DEFAULT_COLOR));
        type_hover_qss = QString("color:#606266;background-color:%1;").arg(MACRO_STR(DEFAULT_HOVER_COLOR));
        break;
        break;
    case qel::ButtonType::Warning:
        break;
    case qel::ButtonType::Danger:
        break;
    case qel::ButtonType::Info:
        break;
    case qel::ButtonType::Text:
        break;
    case ButtonType::Primary:
        type_qss = QString("color:white;background-color:%1;").arg(MACRO_STR(PRIMARY_COLOR));
        type_hover_qss = QString("color:white;background-color:%1;").arg(MACRO_STR(PRIMARY_HOVER_COLOR));
        break;
    case ButtonType::Success:
        type_qss = QString("color:white;background-color:%1;").arg(MACRO_STR(SUCCESS_COLOR));
        type_hover_qss = QString("color:white;background-color:%1;").arg(MACRO_STR(SUCCESS_HOVER_COLOR));
        break;
    default:
        break;
    }


    QString round_qss;
    if (is_round_)
        round_qss = QString("border-radius:%1px;").arg(QString::number(this->height()/2));
    else
        round_qss = QString("border-radius:4px;");

    if (is_circle_)
    {
        round_qss = QString("border-radius:%1px;").arg(QString::number(this->height()/2));
        this->setFixedWidth(this->height());
    }

    this->setStyleSheet(QString("QPushButton{")
                        + type_qss
                        + round_qss
                        + "}"
                        + "QPushButton:hover{"
                        + type_hover_qss
                        + round_qss
                        + "}");

   this->setText(btn_text_);
}

}   // namespace qel
