#ifndef BUTTONPAGE_H
#define BUTTONPAGE_H

#include <QWidget>
#include <QGridLayout>

#include "../QelButton/QelButton.h"

class ButtonPage : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonPage(QWidget *parent = nullptr);

signals:

public slots:

private:
    qel::QelButton *p_qel_btn_default_;
    qel::QelButton *p_qel_btn_primary_;
    qel::QelButton *p_qel_button_primary2_;
    qel::QelButton *p_qel_button_success1_;
    QGridLayout    *p_btn_lyt;
};

#endif // BUTTONPAGE_H
