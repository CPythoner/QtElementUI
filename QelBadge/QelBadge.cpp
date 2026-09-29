#include "QelBadge.h"

#include "../QelCommon/QelControlTypes.h"
#include "../QelTheme/QelTheme.h"

#include <QColor>
#include <QFontMetrics>
#include <QHBoxLayout>
#include <QLabel>
#include <QMetaType>
#include <QPainter>
#include <QPalette>
#include <QResizeEvent>
#include <QShowEvent>

namespace qel {

namespace {

constexpr int kBadgeHeight = 18;
constexpr int kBadgeRadius = 9;
constexpr int kBadgeHorizontalPadding = 6;
constexpr int kDotSize = 8;
constexpr int kNormalAnchorInset = 10;
constexpr int kDotAnchorInset = 5;

QelSemanticType toSemanticType(QelBadge::Type type)
{
    switch (type) {
    case QelBadge::Type::Primary:
        return QelSemanticType::Primary;
    case QelBadge::Type::Success:
        return QelSemanticType::Success;
    case QelBadge::Type::Warning:
        return QelSemanticType::Warning;
    case QelBadge::Type::Info:
        return QelSemanticType::Info;
    case QelBadge::Type::Danger:
    default:
        return QelSemanticType::Danger;
    }
}

bool isNumericMetaType(int typeId)
{
    switch (typeId) {
    case QMetaType::Int:
    case QMetaType::UInt:
    case QMetaType::LongLong:
    case QMetaType::ULongLong:
    case QMetaType::Double:
    case QMetaType::Float:
        return true;
    default:
        return false;
    }
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

    result = result.expandedTo(widget->minimumSize());

    const QSize maximum = widget->maximumSize();
    result.setWidth(qMin(result.width(), maximum.width()));
    result.setHeight(qMin(result.height(), maximum.height()));

    return result;
}

} // namespace

class QelBadgeBubble : public QWidget
{
public:
    explicit QelBadgeBubble(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setAttribute(Qt::WA_TranslucentBackground, true);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        layout_ = new QHBoxLayout(this);
        layout_->setSpacing(0);
        layout_->setContentsMargins(
            kBadgeHorizontalPadding,
            0,
            kBadgeHorizontalPadding,
            0);

        label_ = new QLabel(this);
        label_->setAlignment(Qt::AlignCenter);
        label_->setTextFormat(Qt::PlainText);
        layout_->addWidget(label_);

        applyTextStyle();
    }

    void setText(const QString &text)
    {
        label_->setText(text);
        updateMetrics();
    }

    void setDot(bool dot)
    {
        if (dot_ == dot) {
            return;
        }

        dot_ = dot;
        label_->setVisible(!dot_ && customContent_ == nullptr);
        updateMetrics();
        update();
    }

    void setBackgroundColor(const QString &color)
    {
        backgroundColor_ = color;
        update();
    }

    void setExternalStyleSheet(const QString &styleSheet)
    {
        externalStyleSheet_ = styleSheet;
        applyTextStyle();
    }

    void setBadgeClass(const QString &className)
    {
        setProperty("qel-badge-class", className);
    }

    void setContentWidget(QWidget *widget)
    {
        if (customContent_ == widget) {
            return;
        }

        if (customContent_ != nullptr) {
            layout_->removeWidget(customContent_);
            customContent_->deleteLater();
            customContent_ = nullptr;
        }

        if (widget == nullptr) {
            label_->setVisible(!dot_);
            updateMetrics();
            return;
        }

        customContent_ = widget;
        customContent_->setParent(this);
        customContent_->setPalette(palette());
        label_->hide();
        layout_->addWidget(customContent_);
        customContent_->show();

        updateMetrics();
    }

    QWidget *contentWidget() const
    {
        return customContent_;
    }

    QWidget *takeContentWidget()
    {
        if (customContent_ == nullptr) {
            return nullptr;
        }

        QWidget *widget = customContent_;
        layout_->removeWidget(widget);
        widget->hide();
        widget->setParent(nullptr);
        customContent_ = nullptr;
        label_->setVisible(!dot_);
        updateMetrics();
        return widget;
    }

    QSize sizeHint() const override
    {
        if (dot_) {
            return QSize(kDotSize, kDotSize);
        }

        int contentWidth = label_->fontMetrics().horizontalAdvance(label_->text());
        int contentHeight = label_->fontMetrics().height();

        if (customContent_ != nullptr) {
            const QSize customHint = effectiveWidgetSize(customContent_);
            contentWidth = qMax(contentWidth, customHint.width());
            contentHeight = qMax(contentHeight, customHint.height());
        }

        const int width =
            qMax(kBadgeHeight, contentWidth + 2 * kBadgeHorizontalPadding);
        const int height = qMax(kBadgeHeight, contentHeight);

        return QSize(width, height);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        const QelTheme::ColorTokens &colors = QelTheme::colors();
        painter.setPen(QPen(QColor(colors.fillBlank), 1.0));
        painter.setBrush(QColor(backgroundColor_));

        const qreal radius = dot_ ? kDotSize / 2.0 : kBadgeRadius;
        painter.drawRoundedRect(
            QRectF(rect()).adjusted(0.5, 0.5, -0.5, -0.5),
            radius,
            radius);
    }

private:
    void updateMetrics()
    {
        if (dot_) {
            layout_->setContentsMargins(0, 0, 0, 0);
            setFixedSize(kDotSize, kDotSize);
        } else {
            layout_->setContentsMargins(
                kBadgeHorizontalPadding,
                0,
                kBadgeHorizontalPadding,
                0);
            const QSize hint = sizeHint();
            setFixedSize(hint);
        }

        updateGeometry();
    }

    void applyTextStyle()
    {
        const QelTheme::ColorTokens &colors = QelTheme::colors();

        QPalette textPalette = palette();
        textPalette.setColor(QPalette::WindowText, QColor(colors.fillBlank));
        setPalette(textPalette);
        label_->setPalette(textPalette);

        label_->setStyleSheet(
            QString(
                "QLabel {"
                " color: %1;"
                " background: transparent;"
                " border: none;"
                " font-size: 12px;"
                "}")
                .arg(colors.fillBlank));

        if (customContent_ != nullptr) {
            customContent_->setPalette(textPalette);
        }

        QWidget::setStyleSheet(externalStyleSheet_);
    }

    QHBoxLayout *layout_ = nullptr;
    QLabel *label_ = nullptr;
    QWidget *customContent_ = nullptr;

    bool dot_ = false;
    QString backgroundColor_;
    QString externalStyleSheet_;
};

QelBadge::QelBadge(QWidget *parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    bubble_ = new QelBadgeBubble(this);
    bubble_->hide();

    updateBadge();
}

QelBadge::~QelBadge()
{
    if (contentWidget_ != nullptr) {
        delete contentWidget_;
        contentWidget_ = nullptr;
    }

    if (bubble_ != nullptr && bubble_->contentWidget() != nullptr) {
        QWidget *content = bubble_->takeContentWidget();
        delete content;
    }
}

void QelBadge::setValue(const QVariant &value)
{
    value_ = value;
    updateBadge();
}

QVariant QelBadge::value() const
{
    return value_;
}

QString QelBadge::displayText() const
{
    if (dot_) {
        return QString();
    }

    if (isNumericValue() && value_.toDouble() > max_) {
        return QString::number(max_, 'g', 15) + "+";
    }

    return value_.toString();
}

void QelBadge::setMax(double max)
{
    max_ = max;
    updateBadge();
}

double QelBadge::max() const
{
    return max_;
}

void QelBadge::setDot(bool dot)
{
    dot_ = dot;
    updateBadge();
}

bool QelBadge::isDot() const
{
    return dot_;
}

void QelBadge::setHidden(bool hidden)
{
    hidden_ = hidden;
    updateBadge();
}

bool QelBadge::isHidden() const
{
    return hidden_;
}

void QelBadge::setType(Type type)
{
    type_ = type;
    updateBadge();
}

QelBadge::Type QelBadge::type() const
{
    return type_;
}

void QelBadge::setShowZero(bool show)
{
    showZero_ = show;
    updateBadge();
}

bool QelBadge::showZero() const
{
    return showZero_;
}

void QelBadge::setColor(const QString &color)
{
    color_ = color;
    updateBadge();
}

QString QelBadge::color() const
{
    return color_;
}

void QelBadge::setBadgeStyle(const QString &styleSheet)
{
    badgeStyle_ = styleSheet;
    bubble_->setExternalStyleSheet(badgeStyle_);
}

QString QelBadge::badgeStyle() const
{
    return badgeStyle_;
}

void QelBadge::setOffset(const QPoint &offset)
{
    offset_ = offset;
    updateGeometry();
    updateChildGeometry();
}

QPoint QelBadge::offset() const
{
    return offset_;
}

void QelBadge::setBadgeClass(const QString &className)
{
    badgeClass_ = className;
    bubble_->setBadgeClass(badgeClass_);
}

QString QelBadge::badgeClass() const
{
    return badgeClass_;
}

void QelBadge::setContentWidget(QWidget *widget)
{
    if (contentWidget_ == widget) {
        return;
    }

    if (contentWidget_ != nullptr) {
        contentWidget_->deleteLater();
        contentWidget_ = nullptr;
    }

    contentWidget_ = widget;
    if (contentWidget_ != nullptr) {
        contentWidget_->setParent(this);
        contentWidget_->show();
    }

    updateGeometry();
    adjustSize();
    updateChildGeometry();
}

QWidget *QelBadge::contentWidget() const
{
    return contentWidget_;
}

void QelBadge::setBadgeContentWidget(QWidget *widget)
{
    badgeContentRenderer_ = BadgeContentRenderer();
    bubble_->setContentWidget(widget);
    updateBadge();
}

QWidget *QelBadge::badgeContentWidget() const
{
    return bubble_->contentWidget();
}

void QelBadge::setBadgeContentRenderer(
    const BadgeContentRenderer &renderer)
{
    badgeContentRenderer_ = renderer;
    updateBadge();
}

void QelBadge::clearBadgeContentRenderer()
{
    badgeContentRenderer_ = BadgeContentRenderer();
    bubble_->setContentWidget(nullptr);
    updateBadge();
}

bool QelBadge::hasBadgeContentRenderer() const
{
    return static_cast<bool>(badgeContentRenderer_);
}

QSize QelBadge::sizeHint() const
{
    const bool showBadge = shouldShowBadge();
    const QSize badgeSize = showBadge ? bubble_->sizeHint() : QSize();

    if (contentWidget_ == nullptr) {
        return showBadge ? badgeSize : QSize(0, 0);
    }

    const QSize contentSize = effectiveWidgetSize(contentWidget_);
    if (!showBadge) {
        return contentSize;
    }

    const int anchorInset = dot_ ? kDotAnchorInset : kNormalAnchorInset;
    const int halfBadgeHeight = badgeSize.height() / 2;

    const int topInset =
        qMax(0, halfBadgeHeight - offset_.y());

    const int desiredBadgeLeft =
        contentSize.width() - anchorInset + offset_.x();
    const int leftInset =
        qMax(0, -desiredBadgeLeft);

    const int normalizedBadgeLeft =
        leftInset + desiredBadgeLeft;
    const int badgeRight =
        normalizedBadgeLeft + badgeSize.width();

    const int contentRight =
        leftInset + contentSize.width();
    const int rightInset =
        qMax(0, badgeRight - contentRight);

    const int badgeBottom =
        topInset - halfBadgeHeight + offset_.y()
        + badgeSize.height();
    const int contentBottom =
        topInset + contentSize.height();
    const int bottomInset =
        qMax(0, badgeBottom - contentBottom);

    return QSize(
        leftInset + contentSize.width() + rightInset,
        topInset + contentSize.height() + bottomInset);
}

QSize QelBadge::minimumSizeHint() const
{
    return sizeHint();
}

void QelBadge::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateChildGeometry();
}

void QelBadge::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    updateChildGeometry();
}

void QelBadge::updateBadge()
{
    updateRenderedBadgeContent();

    const QString background =
        !color_.isEmpty() && QColor(color_).isValid()
            ? QColor(color_).name()
            : QelTheme::semanticColor(toSemanticType(type_));

    bubble_->setBackgroundColor(background);
    bubble_->setDot(dot_);
    bubble_->setText(displayText());
    bubble_->setBadgeClass(badgeClass_);
    bubble_->setExternalStyleSheet(badgeStyle_);
    bubble_->setVisible(shouldShowBadge());

    updateGeometry();
    adjustSize();
    updateChildGeometry();
}

void QelBadge::updateRenderedBadgeContent()
{
    if (!badgeContentRenderer_) {
        return;
    }

    QWidget *rendered =
        badgeContentRenderer_(displayText(), bubble_);
    bubble_->setContentWidget(rendered);
}

void QelBadge::updateChildGeometry()
{
    const bool showBadge = shouldShowBadge();

    if (contentWidget_ == nullptr) {
        if (showBadge) {
            const QSize badgeSize = bubble_->sizeHint();
            bubble_->setGeometry(QRect(QPoint(0, 0), badgeSize));
        }
        return;
    }

    const QSize contentSize = effectiveWidgetSize(contentWidget_);

    if (!showBadge) {
        contentWidget_->setGeometry(
            QRect(QPoint(0, 0), contentSize));
        return;
    }

    const QSize badgeSize = bubble_->sizeHint();
    const int anchorInset = dot_ ? kDotAnchorInset : kNormalAnchorInset;
    const int halfBadgeHeight = badgeSize.height() / 2;

    const int desiredBadgeLeft =
        contentSize.width() - anchorInset + offset_.x();
    const int leftInset =
        qMax(0, -desiredBadgeLeft);
    const int topInset =
        qMax(0, halfBadgeHeight - offset_.y());

    contentWidget_->setGeometry(
        QRect(QPoint(leftInset, topInset), contentSize));

    const int badgeLeft =
        leftInset + desiredBadgeLeft;
    const int badgeTop =
        topInset - halfBadgeHeight + offset_.y();

    bubble_->setGeometry(
        QRect(QPoint(badgeLeft, badgeTop), badgeSize));
    bubble_->raise();
}

bool QelBadge::shouldShowBadge() const
{
    if (hidden_) {
        return false;
    }

    if (!showZero_ && isZeroValue()) {
        return false;
    }

    if (dot_ || bubble_->contentWidget() != nullptr) {
        return true;
    }

    return !displayText().isEmpty();
}

bool QelBadge::isNumericValue() const
{
    return value_.isValid()
        && isNumericMetaType(value_.userType());
}

bool QelBadge::isZeroValue() const
{
    return isNumericValue()
        && qFuzzyIsNull(value_.toDouble());
}

} // namespace qel
