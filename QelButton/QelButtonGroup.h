#ifndef QELBUTTONGROUP_H
#define QELBUTTONGROUP_H

#include <QWidget>
#include <QHBoxLayout>
#include "QelButton.h"

namespace qel {

class QelButtonGroup : public QWidget
{
    Q_OBJECT

public:
    explicit QelButtonGroup(QWidget *parent = nullptr);

    // 添加按钮到组
    void addButton(QelButton* button);

    // 设置按钮组大小
    void setSize(QelButton::ButtonSize size);

    // 设置按钮组类型
    void setType(QelButton::ButtonType type);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void initUI();
    void updateStyle();

    QHBoxLayout* m_layout;
    QList<QelButton*> m_buttons;
    QelButton::ButtonSize m_size;
    QelButton::ButtonType m_type;
};

} // namespace qel

#endif // QELBUTTONGROUP_H
