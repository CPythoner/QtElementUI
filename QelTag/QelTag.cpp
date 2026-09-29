#include "QelTag.h"

#include "../QelAnimationHelper/QelAnimationHelper.h"
#include "../QelTheme/QelTheme.h"

#include <QColor>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QShowEvent>
#include <QToolButton>

namespace qel {

namespace {

struct TagMetrics {
    int height = 24;
    int horizontalPadding = 10;
    int closeGap = 6;
    int closeSize = 14;
};

TagMetrics metricsForSize(QelTag::Size size)
{
    switch (size) {
    case QelTag::Size::Large:
        return {32, 12, 8, 16};
    case QelTag::Size::Small:
        return {20, 8, 4, 12};
    case QelTag::Size::Default:
    default:
        return {24, 10, 6, 14};
    }
}

QelSemanticType toSemanticType(QelTag::Type type)
{
    switch (type) {
    case QelTag::Type::Success:
        return QelSemanticType::Success;
    case QelTag::Type::Info:
        return QelSemanticType::Info;
    case QelTag::Type::Warning:
        return QelSemanticType::Warning;
    case QelTag::Type::Danger:
        return QelSemanticType::Danger;
    case QelTag::Type::Primary:
    default:
        return QelSemanticType::Primary;
    }
}

QString semanticBase(QelTag::Type type)
{
    return QelTheme::semanticColor(toSemanticType(type));
}

QString lightColor(QelTag::Type type, int level)
{
    return QelTheme::semanticLightColor(toSemanticType(type), level);
}

} // namespace

QelTag::QelTag(const QString &text,
               Type type,
               Size size,
               Effect effect,
               QWidget *parent)
    : QWidget(parent)
    , type_(type)
    , size_(size)
    , effect_(effect)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    layout_ = new QHBoxLayout(this);
    layout_->setSpacing(0);

    label_ = new QLabel(text, this);
    label_->setAlignment(Qt::AlignCenter);
    label_->setTextFormat(Qt::PlainText);
    layout_->addWidget(label_);

    closeButton_ = new QToolButton(this);
    closeButton_->setText(QString::fromUtf8("×"));
    closeButton_->setAutoRaise(true);
    closeButton_->setCursor(Qt::PointingHandCursor);
    closeButton_->setFocusPolicy(Qt::StrongFocus);
    closeButton_->hide();

    connect(closeButton_, &QToolButton::clicked, this, [this]() {
        emit closeRequested();
    });

    layout_->addWidget(closeButton_);

    updateLayoutMetrics();
    updateStyle();
}

void QelTag::setText(const QString &text)
{
    label_->setText(text);
}

QString QelTag::text() const
{
    return label_->text();
}

void QelTag::setType(Type type)
{
    type_ = type;
    updateStyle();
}

QelTag::Type QelTag::type() const
{
    return type_;
}

void QelTag::setClosable(bool closable)
{
    closable_ = closable;
    closeButton_->setVisible(closable_);
    updateLayoutMetrics();
}

bool QelTag::isClosable() const
{
    return closable_;
}

void QelTag::setDisableTransitions(bool disabled)
{
    disableTransitions_ = disabled;
}

bool QelTag::transitionsDisabled() const
{
    return disableTransitions_;
}

void QelTag::setHit(bool hit)
{
    hit_ = hit;
    updateStyle();
}

bool QelTag::isHit() const
{
    return hit_;
}

void QelTag::setColor(const QString &color)
{
    color_ = color;
    updateStyle();
}

QString QelTag::color() const
{
    return color_;
}

void QelTag::setSize(Size size)
{
    size_ = size;
    updateLayoutMetrics();
    updateStyle();
}

QelTag::Size QelTag::size() const
{
    return size_;
}

void QelTag::setEffect(Effect effect)
{
    effect_ = effect;
    updateStyle();
}

QelTag::Effect QelTag::effect() const
{
    return effect_;
}

void QelTag::setRound(bool round)
{
    round_ = round;
    updateStyle();
}

bool QelTag::isRound() const
{
    return round_;
}

void QelTag::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const QColor background(backgroundColor_);
    const QColor border(borderColor_);
    const qreal radius = round_ ? height() / 2.0 : 4.0;

    painter.setPen(QPen(border, 1.0));
    painter.setBrush(background);
    painter.drawRoundedRect(
        QRectF(rect()).adjusted(0.5, 0.5, -0.5, -0.5),
        radius,
        radius);
}

void QelTag::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);

    if (event->button() == Qt::LeftButton
        && rect().contains(event->pos())) {
        emit clicked();
    }
}

void QelTag::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    if (!disableTransitions_ && !transitionPlayed_) {
        transitionPlayed_ = true;
        QelAnimationHelper::fadeIn(this, 160);
    }
}

void QelTag::updateLayoutMetrics()
{
    const TagMetrics metrics = metricsForSize(size_);
    setFixedHeight(metrics.height);

    const int rightPadding =
        closable_ ? qMax(0, metrics.closeGap - 1)
                  : metrics.horizontalPadding;

    layout_->setContentsMargins(
        metrics.horizontalPadding,
        0,
        rightPadding,
        0);

    layout_->setSpacing(closable_ ? metrics.closeGap : 0);

    closeButton_->setFixedSize(metrics.closeSize, metrics.closeSize);
}

void QelTag::updateStyle()
{
    const QelTheme::ColorTokens &colors = QelTheme::colors();
    const QString base = semanticBase(type_);

    QString background;
    QString border;
    QString text;
    QString closeHover;

    switch (effect_) {
    case Effect::Dark:
        background = base;
        border = base;
        text = colors.fillBlank;
        closeHover = lightColor(type_, 3);
        break;

    case Effect::Plain:
        background = colors.fillBlank;
        border = lightColor(type_, 5);
        text = base;
        closeHover = base;
        break;

    case Effect::Light:
    default:
        background = lightColor(type_, 9);
        border = lightColor(type_, 8);
        text = base;
        closeHover = base;
        break;
    }

    const QColor customBackground(color_);
    if (!color_.isEmpty() && customBackground.isValid()) {
        background = customBackground.name();
    }

    if (hit_) {
        border = base;
    }

    backgroundColor_ = background;
    borderColor_ = border;
    update();

    setStyleSheet(
        QString(
            "QLabel {"
            " color: %1;"
            " background: transparent;"
            " border: none;"
            " font-size: 12px;"
            "}"
            "QToolButton {"
            " color: %1;"
            " background: transparent;"
            " border: none;"
            " border-radius: %2px;"
            " padding: 0px;"
            " font-size: %3px;"
            " font-weight: 600;"
            "}"
            "QToolButton:hover {"
            " color: %4;"
            " background-color: %5;"
            "}"
            "QToolButton:focus {"
            " border: 2px solid %6;"
            "}")
            .arg(text)
            .arg(qMax(1, metricsForSize(size_).closeSize / 2))
            .arg(metricsForSize(size_).closeSize)
            .arg(colors.fillBlank)
            .arg(closeHover)
            .arg(colors.primary));
}

} // namespace qel
