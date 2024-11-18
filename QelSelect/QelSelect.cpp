#include "QelSelect.h"
#include <QPainter>
#include <QStyleOption>
#include <QApplication>

QelSelect::QelSelect(QWidget* parent)
    : QComboBox(parent)
    , m_placeholder("")
    , m_clearable(false)
    , m_disabled(false)
    , m_filterable(false)
{
    initUI();
    setupStyle();
}

void QelSelect::initUI()
{
    setEditable(true);
    m_lineEdit = new QLineEdit(this);
    setLineEdit(m_lineEdit);

    // 设置默认最小尺寸
    setMinimumSize(240, 32);

    // 设置下拉框弹出方式
    setMaxVisibleItems(6);  // 最多显示6个选项
    setSizeAdjustPolicy(QComboBox::AdjustToContents);
    view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // 设置下拉框样式
    view()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    view()->setAttribute(Qt::WA_TranslucentBackground);

    // 禁用 QLineEdit 的编辑功能，但保持其可见
    m_lineEdit->setReadOnly(true);

    // 连接信号槽
    connect(this, QOverload<int>::of(&QComboBox::activated),
            this, &QelSelect::handleActivated);
}

void QelSelect::setupStyle()
{
    // 更新样式
    QString style = R"(
        QelSelect {
            border: 1px solid #dcdfe6;
            border-radius: 4px;
            padding: 0 30px 0 15px;
            background-color: #ffffff;
            min-height: 32px;
        }
        QelSelect:hover {
            border-color: #c0c4cc;
        }
        QelSelect:focus {
            border-color: #409eff;
        }
        QelSelect[disabled="true"] {
            background-color: #f5f7fa;
            border-color: #e4e7ed;
            color: #c0c4cc;
            cursor: not-allowed;
        }
        QelSelect::drop-down {
            border: none;
            width: 20px;
            padding-right: 5px;
        }
        QelSelect::down-arrow {
            image: url(:/icons/arrow-down.svg);
            width: 12px;
            height: 12px;
        }
        QelSelect::down-arrow:disabled {
            image: url(:/icons/arrow-down-disabled.svg);
        }
        QelSelect QLineEdit {
            border: none;
            background: transparent;
            padding: 0;
        }
        QelSelect QListView {
            border: 1px solid #e4e7ed;
            background: white;
            border-radius: 4px;
            padding: 6px 0;
            margin-top: 5px;
        }
        QelSelect QListView::item {
            height: 34px;
            padding: 0 20px;
            color: #606266;
        }
        QelSelect QListView::item:hover {
            background: #f5f7fa;
        }
        QelSelect QListView::item:selected {
            background: #f5f7fa;
            color: #409eff;
        }
    )";

    setStyleSheet(style);
}

QString QelSelect::placeholder() const
{
    return m_placeholder;
}

void QelSelect::setPlaceholder(const QString& placeholder)
{
    m_placeholder = placeholder;
    if (m_lineEdit)
    {
        m_lineEdit->setPlaceholderText(placeholder);
    }
}

bool QelSelect::clearable() const
{
    return m_clearable;
}

void QelSelect::setClearable(bool clearable)
{
    m_clearable = clearable;
    if (m_lineEdit)
    {
        m_lineEdit->setClearButtonEnabled(clearable);
    }
}

bool QelSelect::isDisabled() const
{
    return m_disabled;
}

void QelSelect::setDisabled(bool disabled)
{
    m_disabled = disabled;
    QComboBox::setDisabled(disabled);
}

bool QelSelect::filterable() const
{
    return m_filterable;
}

void QelSelect::setFilterable(bool filterable)
{
    m_filterable = filterable;
    setEditable(filterable);
}

void QelSelect::paintEvent(QPaintEvent* event)
{
    QComboBox::paintEvent(event);

    // 绘制自定义样式
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 如果需要绘制其他内容，在这里添加
}

void QelSelect::focusInEvent(QFocusEvent* event)
{
    QComboBox::focusInEvent(event);
    update();
}

void QelSelect::focusOutEvent(QFocusEvent* event)
{
    QComboBox::focusOutEvent(event);
    update();
}

// 添加新的槽函数
void QelSelect::handleActivated(int index)
{
    if (m_lineEdit && index >= 0) {
        m_lineEdit->setText(itemText(index));
    }
}

// 重写鼠标事件
void QelSelect::mousePressEvent(QMouseEvent* event)
{
    if (!isEnabled()) {
        return;
    }

    // 显示或隐藏下拉列表
    if (!view()->isVisible()) {
        showPopup();
    } else {
        hidePopup();
    }

    event->accept();
}
