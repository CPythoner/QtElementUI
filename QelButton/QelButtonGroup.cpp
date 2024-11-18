#include "QelButtonGroup.h"
#include <QPainter>
#include <QPainterPath>

namespace qel {

QelButtonGroup::QelButtonGroup(QWidget *parent)
    : QWidget(parent)
    , m_size(QelButton::Medium)
    , m_type(QelButton::Default)
{
    initUI();
    updateStyle();
}

void QelButtonGroup::initUI()
{
    m_layout = new QHBoxLayout(this);
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_layout);
}

void QelButtonGroup::addButton(QelButton* button)
{
    if (!button) return;

    m_buttons.append(button);
    m_layout->addWidget(button);

    // 更新按钮样式
    button->setSize(m_size);
    button->setType(m_type);

    // 特殊处理第一个和最后一个按钮的圆角
    updateStyle();
}

void QelButtonGroup::setSize(QelButton::ButtonSize size)
{
    m_size = size;
    for (QelButton* btn : m_buttons) {
        btn->setSize(size);
    }
}

void QelButtonGroup::setType(QelButton::ButtonType type)
{
    m_type = type;
    for (QelButton* btn : m_buttons) {
        btn->setType(type);
    }
}

void QelButtonGroup::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
}

void QelButtonGroup::updateStyle()
{
    if (m_buttons.isEmpty()) return;

    QString baseStyle = R"(
        QelButtonGroup {
            border: none;
            background: transparent;
        }
    )";

    // 设置按钮组的样式
    for (int i = 0; i < m_buttons.size(); ++i) {
        QelButton* btn = m_buttons[i];
        QString btnStyle;

        if (i == 0) {
            // 第一个按钮：左边有圆角，右边没有
            btnStyle = QString(R"(
                QPushButton {
                    border-top-right-radius: 0;
                    border-bottom-right-radius: 0;
                    border-right: none;
                    margin: 0;
                }
                QPushButton:hover {
                    position: relative;
                    z-index: 1;
                    border-right: 1px solid %1;
                }
            )").arg(btn->property("type") == QelButton::Primary ? "#66b1ff" : "#c0c4cc");
        } else if (i == m_buttons.size() - 1) {
            // 最后一个按钮：右边有圆角，左边没有
            btnStyle = QString(R"(
                QPushButton {
                    border-top-left-radius: 0;
                    border-bottom-left-radius: 0;
                    margin: 0;
                    margin-left: -1px;
                }
                QPushButton:hover {
                    position: relative;
                    z-index: 1;
                }
            )");
        } else {
            // 中间的按钮：两边都没有圆角
            btnStyle = QString(R"(
                QPushButton {
                    border-radius: 0;
                    border-right: none;
                    margin: 0;
                    margin-left: -1px;
                }
                QPushButton:hover {
                    position: relative;
                    z-index: 1;
                    border-right: 1px solid %1;
                }
            )").arg(btn->property("type") == QelButton::Primary ? "#66b1ff" : "#c0c4cc");
        }

        // 合并现有样式和新样式
        QString currentStyle = btn->styleSheet();
        if (!currentStyle.isEmpty()) {
            currentStyle += "\n";
        }
        btn->setStyleSheet(currentStyle + btnStyle);
    }

    setStyleSheet(baseStyle);

    // 更新布局
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0, 0, 0, 0);
}

} // namespace qel
