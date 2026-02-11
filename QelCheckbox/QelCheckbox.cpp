#include "QelCheckbox.h"

#include <QPainter>
#include <QProxyStyle>
#include <QStyleOption>

namespace qel {

namespace {

class QelCheckboxStyle : public QProxyStyle
{
public:
    explicit QelCheckboxStyle(int indicatorSize)
        : indicatorSize_(indicatorSize)
    {
    }

    int pixelMetric(PixelMetric metric,
                    const QStyleOption *option = nullptr,
                    const QWidget *widget = nullptr) const override
    {
        if (metric == PM_IndicatorWidth || metric == PM_IndicatorHeight) {
            return indicatorSize_;
        }

        return QProxyStyle::pixelMetric(metric, option, widget);
    }

    void drawPrimitive(PrimitiveElement element,
                       const QStyleOption *option,
                       QPainter *painter,
                       const QWidget *widget = nullptr) const override
    {
        if (element != PE_IndicatorCheckBox || option == nullptr || painter == nullptr) {
            QProxyStyle::drawPrimitive(element, option, painter, widget);
            return;
        }

        const bool enabled = (option->state & State_Enabled);
        const bool hovered = (option->state & State_MouseOver);
        const bool checked = (option->state & State_On);
        const bool indeterminate = (option->state & State_NoChange);

        QColor borderColor = QColor("#DCDFE6");
        QColor bgColor = QColor("#FFFFFF");

        if (!enabled) {
            borderColor = QColor("#E4E7ED");
            bgColor = QColor("#F5F7FA");
        }

        if (hovered && enabled && !checked && !indeterminate) {
            borderColor = QColor("#409EFF");
        }

        if (checked || indeterminate) {
            borderColor = enabled ? QColor("#409EFF") : QColor("#B3D8FF");
            bgColor = borderColor;
        }

        const QRectF rect = option->rect.adjusted(0.5, 0.5, -0.5, -0.5);

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setPen(QPen(borderColor, 1.0));
        painter->setBrush(bgColor);
        painter->drawRoundedRect(rect, 2.5, 2.5);

        if (checked || indeterminate) {
            painter->setPen(QPen(Qt::white, 2.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

            if (indeterminate) {
                const qreal centerY = rect.center().y();
                painter->drawLine(QPointF(rect.left() + rect.width() * 0.25, centerY),
                                  QPointF(rect.right() - rect.width() * 0.25, centerY));
            } else {
                const QPointF p1(rect.left() + rect.width() * 0.22, rect.top() + rect.height() * 0.52);
                const QPointF p2(rect.left() + rect.width() * 0.44, rect.bottom() - rect.height() * 0.24);
                const QPointF p3(rect.right() - rect.width() * 0.20, rect.top() + rect.height() * 0.26);
                painter->drawLine(p1, p2);
                painter->drawLine(p2, p3);
            }
        }

        painter->restore();
    }

private:
    int indicatorSize_ = 14;
};

} // namespace

QelCheckbox::QelCheckbox(const QString &text, QWidget *parent)
    : QCheckBox(text, parent)
{
    setTristate(true);
    setCheckState(Qt::Unchecked);
    setCursor(Qt::PointingHandCursor);

    connect(this, &QCheckBox::stateChanged, this, [this](int) {
        update();
    });

    applyStyle();
}

void QelCheckbox::setSize(Size size)
{
    if (size_ == size) {
        return;
    }

    size_ = size;
    applyStyle();
}

void QelCheckbox::setBorder(bool border)
{
    if (border_ == border) {
        return;
    }

    border_ = border;
    applyStyle();
}

void QelCheckbox::setIndeterminate(bool indeterminate)
{
    if (indeterminate) {
        setCheckState(Qt::PartiallyChecked);
    } else {
        setCheckState(isChecked() ? Qt::Checked : Qt::Unchecked);
    }
    update();
}

void QelCheckbox::applyStyle()
{
    int indicatorSize = 14;
    int fontSize = 14;
    int spacing = 8;
    int minHeight = 32;
    int horizontalPadding = 14;

    switch (size_) {
    case Size::Large:
        indicatorSize = 16;
        fontSize = 14;
        spacing = 10;
        minHeight = 40;
        horizontalPadding = 18;
        break;
    case Size::Default:
        indicatorSize = 14;
        fontSize = 14;
        spacing = 8;
        minHeight = 32;
        horizontalPadding = 14;
        break;
    case Size::Small:
        indicatorSize = 12;
        fontSize = 12;
        spacing = 6;
        minHeight = 24;
        horizontalPadding = 10;
        break;
    }

    QelCheckboxStyle *style = new QelCheckboxStyle(indicatorSize);
    style->setParent(this);
    setStyle(style);

    QString controlStyle;
    if (border_) {
        controlStyle = QString(
            " border: 1px solid #DCDFE6;"
            " border-radius: 4px;"
            " background: #FFFFFF;"
            " min-height: %1px;"
            " padding-left: %2px;"
            " padding-right: %2px;"
        ).arg(minHeight).arg(horizontalPadding);
    }

    QString styleSheet = QString(
        "QCheckBox {"
        " color: #606266;"
        " spacing: %1px;"
        " font-size: %2px;"
        "%3"
        "}"
        "QCheckBox:hover {"
        " color: #409EFF;"
        "%4"
        "}"
        "QCheckBox:checked {"
        " color: #409EFF;"
        "%5"
        "}"
        "QCheckBox:disabled {"
        " color: #C0C4CC;"
        "%6"
        "}"
        "QCheckBox:focus {"
        " outline: none;"
        "}"
    )
        .arg(spacing)
        .arg(fontSize)
        .arg(controlStyle)
        .arg(border_ ? " border-color: #409EFF;" : "")
        .arg(border_ ? " border-color: #409EFF;" : "")
        .arg(border_ ? " border-color: #EBEEF5; background: #F5F7FA;" : "");

    setStyleSheet(styleSheet);
}

} // namespace qel
