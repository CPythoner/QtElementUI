#include "QelCheckbox.h"

#include "../QelStyleHelper/QelStyleHelper.h"
#include "../QelTheme/QelTheme.h"

#include <QPainter>
#include <QProxyStyle>
#include <QStyleOption>

namespace qel {

namespace {

QelStyleHelper::StateStyleSet indicatorStateStyles()
{
    const QelTheme::ColorTokens &c = QelTheme::colors();

    return {
        {c.fillBlank, c.textRegular, c.borderBase},
        {c.fillBlank, c.textRegular, c.primary},
        {c.primaryLight, c.textRegular, c.primary},
        {c.fillBlank, c.textRegular, c.primary},
        {c.fillLight, c.textPlaceholder, c.borderLight},
        {c.fillLight, c.textPlaceholder, c.borderLight}
    };
}

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

        const bool enabled = option->state & State_Enabled;
        const bool hovered = option->state & State_MouseOver;
        const bool pressed = option->state & State_Sunken;
        const bool focused = option->state & State_HasFocus;
        const bool checked = option->state & State_On;
        const bool indeterminate = option->state & State_NoChange;

        QelStateContext context;
        context.enabled = enabled;
        context.hovered = hovered;
        context.pressed = pressed;
        context.focused = focused;

        const QelVisualState state = QelStyleHelper::resolveState(context);
        const QelStyleHelper::ComponentStyle visual =
            QelStyleHelper::styleForState(indicatorStateStyles(), state);

        const QelTheme::ColorTokens &c = QelTheme::colors();
        QColor borderColor(visual.border);
        QColor bgColor(visual.background);

        if (checked || indeterminate) {
            borderColor = QColor(enabled ? c.primary : c.primaryDisabled);
            bgColor = borderColor;
        }

        const QRectF rect = option->rect.adjusted(1.0, 0.5, -0.5, -0.5);

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setPen(QPen(borderColor, 1.0));
        painter->setBrush(bgColor);
        painter->drawRoundedRect(rect, 2.5, 2.5);

        if (checked || indeterminate) {
            painter->setPen(
                QPen(QColor(c.fillBlank), 2.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

            if (indeterminate) {
                const qreal centerY = rect.center().y();
                painter->drawLine(
                    QPointF(rect.left() + rect.width() * 0.25, centerY),
                    QPointF(rect.right() - rect.width() * 0.25, centerY));
            } else {
                const QPointF p1(
                    rect.left() + rect.width() * 0.22,
                    rect.top() + rect.height() * 0.52);
                const QPointF p2(
                    rect.left() + rect.width() * 0.44,
                    rect.bottom() - rect.height() * 0.24);
                const QPointF p3(
                    rect.right() - rect.width() * 0.20,
                    rect.top() + rect.height() * 0.26);
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
    : QelCheckbox(text, false, false, false, false, Size::Default, parent)
{
}

QelCheckbox::QelCheckbox(const QString &text,
                         bool checked,
                         bool disabled,
                         bool indeterminate,
                         bool border,
                         Size size,
                         QWidget *parent)
    : QCheckBox(text, parent),
      size_(size),
      border_(border)
{
    setTristate(true);
    setCursor(Qt::PointingHandCursor);

    connect(this, &QCheckBox::stateChanged, this, [this](int) {
        update();
    });

    if (indeterminate) {
        setCheckState(Qt::PartiallyChecked);
    } else {
        setChecked(checked);
    }

    setDisabled(disabled);
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

    const QelTheme::ColorTokens &c = QelTheme::colors();

    QString controlStyle;
    if (border_) {
        controlStyle = QString(
            " border: 1px solid %1;"
            " border-radius: 4px;"
            " background: %2;"
            " min-height: %3px;"
            " padding-left: %4px;"
            " padding-right: %4px;"
        )
            .arg(c.borderBase)
            .arg(c.fillBlank)
            .arg(minHeight)
            .arg(horizontalPadding);
    }

    const QString styleSheet = QString(
        "QCheckBox {"
        " color: %1;"
        " spacing: %2px;"
        " font-size: %3px;"
        "%4"
        "}"
        "QCheckBox:hover {"
        " color: %5;"
        "%6"
        "}"
        "QCheckBox:checked {"
        " color: %5;"
        "%7"
        "}"
        "QCheckBox:disabled {"
        " color: %8;"
        "%9"
        "}"
        "QCheckBox:focus {"
        " outline: none;"
        "}"
    )
        .arg(c.textRegular)
        .arg(spacing)
        .arg(fontSize)
        .arg(controlStyle)
        .arg(c.primary)
        .arg(border_ ? QString(" border-color: %1;").arg(c.primary) : QString())
        .arg(border_ ? QString(" border-color: %1;").arg(c.primary) : QString())
        .arg(c.textPlaceholder)
        .arg(border_
                 ? QString(" border-color: %1; background: %2;")
                       .arg(c.borderLighter, c.fillLight)
                 : QString());

    setStyleSheet(styleSheet);
}

} // namespace qel
