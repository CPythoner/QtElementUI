#include "buttonpage.h"
#include <QDebug>

ButtonPage::ButtonPage(QWidget *parent)
    : QWidget(parent),
      p_qel_btn_primary_(new qel::QelButton(this, "Primary", qel::ButtonSize::Medium, qel::ButtonType::Primary))
{
    p_qel_btn_default_ = new qel::QelButton(this, "Default");
    p_qel_button_primary2_ = new qel::QelButton(this, "", qel::ButtonSize::Medium, qel::ButtonType::Primary);
    p_qel_button_success1_ = new qel::QelButton(this, "Success", qel::ButtonSize::Medium, qel::ButtonType::Success);

    this->setFixedSize(800, 600);
    p_btn_lyt = new QGridLayout();

    p_btn_lyt->addWidget(p_qel_btn_default_, 0, 0);
    p_btn_lyt->addWidget(p_qel_btn_primary_, 0, 1);
    p_btn_lyt->addWidget(p_qel_button_primary2_, 1, 1);
    p_btn_lyt->addWidget(p_qel_button_success1_, 0, 2);

    connect(p_qel_button_primary2_, &QPushButton::clicked, this, [&]() {
            qDebug() << "clicked";
        });

    this->setLayout(p_btn_lyt);
}
