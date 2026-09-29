#include "QelProgress.h"

#include "../QelIcon/QelIcon.h"
#include "../QelTheme/QelTheme.h"

#include <algorithm>
#include <cmath>

#include <QColor>
#include <QFontMetrics>
#include <QHideEvent>
#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>
#include <QShowEvent>
#include <QTimer>

namespace qel {

namespace {

constexpr int kDefaultLineWidth = 400;
constexpr int kTextGap = 5;
constexpr int kTextReserve = 50;
constexpr int kAnimationIntervalMs = 16;
constexpr int kProgressTransitionMs = 600;

QString numberText(double value)
{
    return QString::number(value, 'g', 15);
}

QSize effectiveWidgetSize(const QWidget *widget)
{
    if (widget == nullptr) {
        return QSize();
    }

    QSize result = widget->sizeHint();
    if (!result.isValid()) {
        result = QSize(0, 0);
    }

    const QSize minimumHint = widget->minimumSizeHint();
    if (minimumHint.isValid()) {
        result = result.expandedTo(minimumHint);
    }

    return result.expandedTo(widget->minimumSize());
}

} // namespace

QelProgress::QelProgress(QWidget *parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    animationTimer_ = new QTimer(this);
    animationTimer_->setInterval(kAnimationIntervalMs);
    connect(animationTimer_, &QTimer::timeout, this, [this]() {
        if (transitionActive_
            && transitionClock_.isValid()
            && transitionClock_.elapsed() >= kProgressTransitionMs) {
            transitionActive_ = false;
            transitionStartPercentage_ = percentage_;
            updateAnimationState();
        }

        updateContentGeometry();
        update();
    });

    animationClock_.start();
}

QelProgress::~QelProgress()
{
    if (contentWidget_ != nullptr) {
        delete contentWidget_;
        contentWidget_ = nullptr;
    }
}

void QelProgress::setType(Type type)
{
    if (type_ == type) {
        return;
    }

    type_ = type;
    setSizePolicy(
        type_ == Type::Line ? QSizePolicy::Expanding : QSizePolicy::Fixed,
        QSizePolicy::Fixed);

    updateContentWidget();
    updateAnimationState();
    updateGeometry();
    update();
}

QelProgress::Type QelProgress::type() const
{
    return type_;
}

void QelProgress::setPercentage(double percentage)
{
    const double bounded = qBound(0.0, percentage, 100.0);
    if (qFuzzyCompare(percentage_ + 1.0, bounded + 1.0)) {
        return;
    }

    transitionStartPercentage_ = visualPercentage();
    percentage_ = bounded;
    transitionActive_ = true;
    transitionClock_.restart();

    updateContentWidget();
    updateAnimationState();
    updateContentGeometry();
    update();
}

double QelProgress::percentage() const
{
    return percentage_;
}

void QelProgress::setStatus(Status status)
{
    if (status_ == status) {
        return;
    }

    status_ = status;
    update();
}

QelProgress::Status QelProgress::status() const
{
    return status_;
}

void QelProgress::setIndeterminate(bool indeterminate)
{
    if (indeterminate_ == indeterminate) {
        return;
    }

    indeterminate_ = indeterminate;
    updateAnimationState();
    update();
}

bool QelProgress::isIndeterminate() const
{
    return indeterminate_;
}

void QelProgress::setDuration(double seconds)
{
    duration_ = qMax(0.0, seconds);
    animationClock_.restart();
    updateAnimationState();
    update();
}

double QelProgress::duration() const
{
    return duration_;
}

void QelProgress::setStrokeWidth(int width)
{
    strokeWidth_ = qMax(1, width);
    updateContentGeometry();
    updateGeometry();
    update();
}

int QelProgress::strokeWidth() const
{
    return strokeWidth_;
}

void QelProgress::setStrokeLinecap(StrokeLinecap linecap)
{
    strokeLinecap_ = linecap;
    update();
}

QelProgress::StrokeLinecap QelProgress::strokeLinecap() const
{
    return strokeLinecap_;
}

void QelProgress::setTextInside(bool textInside)
{
    textInside_ = textInside;
    updateContentGeometry();
    updateGeometry();
    update();
}

bool QelProgress::textInside() const
{
    return textInside_;
}

void QelProgress::setWidth(int width)
{
    width_ = qMax(1, width);
    updateContentGeometry();
    updateGeometry();
    update();
}

int QelProgress::progressWidth() const
{
    return width_;
}

void QelProgress::setShowText(bool show)
{
    showText_ = show;
    updateContentGeometry();
    updateGeometry();
    update();
}

bool QelProgress::showText() const
{
    return showText_;
}

void QelProgress::setColor(const QString &color)
{
    color_ = color;
    colors_.clear();
    colorFunction_ = ColorFunction();
    update();
}

QString QelProgress::color() const
{
    return color_;
}

void QelProgress::setColors(const QVector<ProgressColor> &colors)
{
    colors_ = colors;
    std::sort(
        colors_.begin(),
        colors_.end(),
        [](const ProgressColor &lhs, const ProgressColor &rhs) {
            return lhs.percentage < rhs.percentage;
        });

    color_.clear();
    colorFunction_ = ColorFunction();
    update();
}

QVector<QelProgress::ProgressColor> QelProgress::colors() const
{
    return colors_;
}

void QelProgress::setColorFunction(const ColorFunction &function)
{
    colorFunction_ = function;
    color_.clear();
    colors_.clear();
    update();
}

bool QelProgress::hasColorFunction() const
{
    return static_cast<bool>(colorFunction_);
}

void QelProgress::clearColor()
{
    color_.clear();
    colors_.clear();
    colorFunction_ = ColorFunction();
    update();
}

void QelProgress::setStriped(bool striped)
{
    striped_ = striped;
    updateAnimationState();
    update();
}

bool QelProgress::isStriped() const
{
    return striped_;
}

void QelProgress::setStripedFlow(bool flow)
{
    stripedFlow_ = flow;
    updateAnimationState();
    update();
}

bool QelProgress::stripedFlow() const
{
    return stripedFlow_;
}

void QelProgress::setFormat(const FormatFunction &format)
{
    format_ = format;
    updateContentWidget();
    update();
}

void QelProgress::clearFormat()
{
    format_ = FormatFunction();
    updateContentWidget();
    update();
}

QString QelProgress::formattedText() const
{
    if (format_) {
        return format_(percentage_);
    }

    return numberText(percentage_) + "%";
}

void QelProgress::setContentRenderer(const ContentRenderer &renderer)
{
    contentRenderer_ = renderer;
    updateContentWidget();
    updateGeometry();
    update();
}

void QelProgress::clearContentRenderer()
{
    contentRenderer_ = ContentRenderer();

    if (contentWidget_ != nullptr) {
        delete contentWidget_;
        contentWidget_ = nullptr;
    }

    updateGeometry();
    update();
}

bool QelProgress::hasContentRenderer() const
{
    return static_cast<bool>(contentRenderer_);
}

QSize QelProgress::sizeHint() const
{
    if (type_ == Type::Circle || type_ == Type::Dashboard) {
        return QSize(width_, width_);
    }

    int height = qMax(strokeWidth_, 18);
    if (contentWidget_ != nullptr) {
        height = qMax(height, effectiveWidgetSize(contentWidget_).height());
    }

    return QSize(kDefaultLineWidth, height + 4);
}

QSize QelProgress::minimumSizeHint() const
{
    if (type_ == Type::Circle || type_ == Type::Dashboard) {
        return sizeHint();
    }

    return QSize(120, sizeHint().height());
}

void QelProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if (type_ == Type::Line) {
        paintLine(painter);
    } else {
        paintCircle(painter, type_ == Type::Dashboard);
    }
}

void QelProgress::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateContentGeometry();
}

void QelProgress::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    updateAnimationState();
    updateContentGeometry();
}

void QelProgress::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);
    if (animationTimer_ != nullptr) {
        animationTimer_->stop();
    }
}

void QelProgress::paintLine(QPainter &painter)
{
    const QelTheme::ColorTokens &theme = QelTheme::colors();
    const QRectF track = lineTrackRect();
    if (!track.isValid() || track.width() <= 0.0) {
        return;
    }

    const qreal radius = track.height() / 2.0;

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(theme.borderLighter));
    painter.drawRoundedRect(track, radius, radius);

    QPainterPath trackClip;
    trackClip.addRoundedRect(track, radius, radius);

    painter.save();
    painter.setClipPath(trackClip);

    QRectF fillRect = track;
    const QColor fillColor(currentColor());

    if (indeterminate_) {
        const qreal segmentWidth =
            track.width() * qMax(0.05, visualPercentage() / 100.0);
        const qreal x =
            track.left() - segmentWidth
            + animationPhase() * (track.width() + segmentWidth * 2.0);
        fillRect.setLeft(x);
        fillRect.setWidth(segmentWidth);
    } else {
        fillRect.setWidth(track.width() * visualPercentage() / 100.0);
    }

    painter.setBrush(fillColor);
    painter.drawRoundedRect(fillRect, radius, radius);

    if (striped_ && fillRect.width() > 0.0) {
        painter.save();

        QPainterPath fillClip;
        fillClip.addRoundedRect(fillRect, radius, radius);
        painter.setClipPath(fillClip, Qt::IntersectClip);

        QColor stripeColor(0, 0, 0, 25);
        painter.setPen(Qt::NoPen);
        painter.setBrush(stripeColor);

        const qreal stripeWidth = qMax<qreal>(8.0, strokeWidth_ * 1.25);
        const qreal offset =
            stripedFlow_ ? animationPhase() * stripeWidth * 2.0 : 0.0;

        for (qreal x = fillRect.left() - stripeWidth * 2.0 + offset;
             x < fillRect.right() + stripeWidth * 2.0;
             x += stripeWidth * 2.0) {
            QPolygonF stripe;
            stripe << QPointF(x, fillRect.bottom())
                   << QPointF(x + stripeWidth, fillRect.bottom())
                   << QPointF(x + stripeWidth * 2.0, fillRect.top())
                   << QPointF(x + stripeWidth, fillRect.top());
            painter.drawPolygon(stripe);
        }

        painter.restore();
    }

    painter.restore();

    if (contentWidget_ != nullptr) {
        return;
    }

    if (!showText_) {
        return;
    }

    if (textInside_) {
        const qreal filledWidth =
            indeterminate_
                ? fillRect.width()
                : track.width() * visualPercentage() / 100.0;

        if (filledWidth < 28.0) {
            return;
        }

        QRectF textRect(
            fillRect.left(),
            track.top(),
            filledWidth - 5.0,
            track.height());

        QFont font = painter.font();
        font.setPixelSize(12);
        painter.setFont(font);
        painter.setPen(Qt::white);
        painter.drawText(textRect, Qt::AlignVCenter | Qt::AlignRight, formattedText());
        return;
    }

    const QRectF textRect(
        track.right() + kTextGap,
        0,
        qMax<qreal>(0.0, width() - track.right() - kTextGap),
        height());

    paintDefaultText(painter, textRect);
}

void QelProgress::paintCircle(QPainter &painter, bool dashboard)
{
    const QelTheme::ColorTokens &theme = QelTheme::colors();
    const QRectF circle = circularRect();
    const qreal inset = strokeWidth_ / 2.0;
    const QRectF arcRect = circle.adjusted(inset, inset, -inset, -inset);

    QPen trackPen(QColor(theme.borderLighter), strokeWidth_);
    trackPen.setCapStyle(qtCapStyle());
    painter.setPen(trackPen);
    painter.setBrush(Qt::NoBrush);

    const int startAngle = dashboard ? 225 * 16 : 90 * 16;
    const int fullSpan = dashboard ? -270 * 16 : -360 * 16;
    painter.drawArc(arcRect, startAngle, fullSpan);

    if (percentage_ > 0.0) {
        QPen progressPen(QColor(currentColor()), strokeWidth_);
        progressPen.setCapStyle(qtCapStyle());
        painter.setPen(progressPen);

        const int progressSpan =
            static_cast<int>(fullSpan * visualPercentage() / 100.0);
        painter.drawArc(arcRect, startAngle, progressSpan);
    }

    if (contentWidget_ != nullptr || !showText_) {
        return;
    }

    paintDefaultText(painter, circle);
}

void QelProgress::paintDefaultText(QPainter &painter, const QRectF &rect)
{
    if (status_ != Status::Normal) {
        QelIcon::Icon iconType = QelIcon::CheckCircle;
        if (status_ == Status::Exception) {
            iconType = QelIcon::TimesCircle;
        } else if (status_ == Status::Warning) {
            iconType = QelIcon::ExclamationTriangle;
        }

        const int iconSize =
            type_ == Type::Line
                ? qMax(14, static_cast<int>(12 + strokeWidth_ * 0.4))
                : qMax(16, static_cast<int>(width_ * 0.111111 + 2));

        const QelIcon icon(iconType, iconSize, QColor(statusColor()));
        const QPixmap pixmap = icon.pixmap(iconSize, iconSize);
        const QPointF topLeft(
            rect.center().x() - pixmap.width() / 2.0,
            rect.center().y() - pixmap.height() / 2.0);
        painter.drawPixmap(topLeft, pixmap);
        return;
    }

    QFont font = painter.font();
    const int textSize =
        type_ == Type::Line
            ? qMax(12, static_cast<int>(12 + strokeWidth_ * 0.4))
            : qMax(12, static_cast<int>(width_ * 0.111111 + 2));
    font.setPixelSize(textSize);
    painter.setFont(font);
    painter.setPen(QColor(QelTheme::colors().textRegular));
    painter.drawText(rect, Qt::AlignCenter, formattedText());
}

void QelProgress::updateAnimationState()
{
    const bool needsAnimation =
        isVisible()
        && (transitionActive_
            || (duration_ > 0.0
                && type_ == Type::Line
                && (indeterminate_ || (striped_ && stripedFlow_))));

    if (needsAnimation) {
        if (!animationClock_.isValid()) {
            animationClock_.start();
        }
        if (!animationTimer_->isActive()) {
            animationClock_.restart();
            animationTimer_->start();
        }
    } else {
        animationTimer_->stop();
    }
}

void QelProgress::updateContentWidget()
{
    if (contentWidget_ != nullptr) {
        delete contentWidget_;
        contentWidget_ = nullptr;
    }

    if (!contentRenderer_) {
        return;
    }

    contentWidget_ = contentRenderer_(percentage_, this);
    if (contentWidget_ != nullptr) {
        contentWidget_->setParent(this);
        contentWidget_->show();
        updateContentGeometry();
    }
}

void QelProgress::updateContentGeometry()
{
    if (contentWidget_ == nullptr) {
        return;
    }

    const QSize contentSize = effectiveWidgetSize(contentWidget_);

    if (type_ == Type::Circle || type_ == Type::Dashboard) {
        contentWidget_->setGeometry(
            QRect(
                QPoint(
                    (width() - contentSize.width()) / 2,
                    (height() - contentSize.height()) / 2),
                contentSize));
        contentWidget_->raise();
        return;
    }

    const QRectF track = lineTrackRect();

    if (textInside_) {
        const qreal filledWidth =
            track.width() * visualPercentage() / 100.0;
        const int x = qMax(
            static_cast<int>(track.left()),
            static_cast<int>(track.left() + filledWidth - contentSize.width() - 5));
        const int y = (height() - contentSize.height()) / 2;
        contentWidget_->setGeometry(QRect(QPoint(x, y), contentSize));
    } else {
        const int x = static_cast<int>(track.right()) + kTextGap;
        const int y = (height() - contentSize.height()) / 2;
        contentWidget_->setGeometry(QRect(QPoint(x, y), contentSize));
    }

    contentWidget_->raise();
}

QRectF QelProgress::lineTrackRect() const
{
    int reserve = 0;
    if (!textInside_ && (showText_ || contentWidget_ != nullptr)) {
        reserve = kTextReserve + kTextGap;
        if (contentWidget_ != nullptr) {
            reserve = effectiveWidgetSize(contentWidget_).width() + kTextGap;
        }
    }

    const qreal trackWidth = qMax(0, width() - reserve);
    const qreal y = (height() - strokeWidth_) / 2.0;

    return QRectF(0.0, y, trackWidth, strokeWidth_);
}

QRectF QelProgress::circularRect() const
{
    const qreal side = qMin(width(), height());
    return QRectF(
        (width() - side) / 2.0,
        (height() - side) / 2.0,
        side,
        side);
}

QString QelProgress::currentColor() const
{
    if (colorFunction_) {
        const QString candidate = colorFunction_(percentage_);
        if (QColor(candidate).isValid()) {
            return QColor(candidate).name();
        }
    }

    if (!colors_.isEmpty()) {
        for (const ProgressColor &item : colors_) {
            if (percentage_ < item.percentage && QColor(item.color).isValid()) {
                return QColor(item.color).name();
            }
        }

        const QString last = colors_.last().color;
        if (QColor(last).isValid()) {
            return QColor(last).name();
        }
    }

    if (!color_.isEmpty() && QColor(color_).isValid()) {
        return QColor(color_).name();
    }

    return statusColor();
}

QString QelProgress::statusColor() const
{
    const QelTheme::ColorTokens &theme = QelTheme::colors();

    if (type_ == Type::Circle || type_ == Type::Dashboard) {
        switch (status_) {
        case Status::Success:
            return "#13CE66";
        case Status::Exception:
            return "#FF4949";
        case Status::Warning:
            return "#E6A23C";
        case Status::Normal:
        default:
            return "#20A0FF";
        }
    }

    switch (status_) {
    case Status::Success:
        return theme.success;
    case Status::Exception:
        return theme.danger;
    case Status::Warning:
        return theme.warning;
    case Status::Normal:
    default:
        return theme.primary;
    }
}

Qt::PenCapStyle QelProgress::qtCapStyle() const
{
    switch (strokeLinecap_) {
    case StrokeLinecap::Butt:
        return Qt::FlatCap;
    case StrokeLinecap::Square:
        return Qt::SquareCap;
    case StrokeLinecap::Round:
    default:
        return Qt::RoundCap;
    }
}

double QelProgress::animationPhase() const
{
    if (!animationClock_.isValid()) {
        return 0.0;
    }

    if (duration_ <= 0.0) {
        return 0.0;
    }

    const double periodMs = duration_ * 1000.0;
    return std::fmod(animationClock_.elapsed(), periodMs) / periodMs;
}

double QelProgress::visualPercentage() const
{
    if (!transitionActive_
        || !transitionClock_.isValid()) {
        return percentage_;
    }

    const double t = qBound(
        0.0,
        transitionClock_.elapsed()
            / static_cast<double>(kProgressTransitionMs),
        1.0);

    const double eased = t * t * (3.0 - 2.0 * t);
    return transitionStartPercentage_
        + (percentage_ - transitionStartPercentage_) * eased;
}

} // namespace qel
