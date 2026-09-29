#ifndef QELBADGE_H
#define QELBADGE_H

#include <functional>

#include <QPoint>
#include <QString>
#include <QVariant>
#include <QWidget>

class QResizeEvent;
class QShowEvent;

namespace qel {

class QelBadgeBubble;

class QelBadge : public QWidget
{
    Q_OBJECT

public:
    using BadgeContentRenderer =
        std::function<QWidget *(const QString &value, QWidget *parent)>;
    enum class Type {
        Primary,
        Success,
        Warning,
        Info,
        Danger
    };

    static constexpr Type Primary = Type::Primary;
    static constexpr Type Success = Type::Success;
    static constexpr Type Warning = Type::Warning;
    static constexpr Type Info = Type::Info;
    static constexpr Type Danger = Type::Danger;

    explicit QelBadge(QWidget *parent = nullptr);
    ~QelBadge() override;

    void setValue(const QVariant &value);
    QVariant value() const;
    QString displayText() const;

    void setMax(double max);
    double max() const;

    void setDot(bool dot);
    bool isDot() const;

    void setHidden(bool hidden);
    bool isHidden() const;

    void setType(Type type);
    Type type() const;

    void setShowZero(bool show);
    bool showZero() const;

    void setColor(const QString &color);
    QString color() const;

    // Element Plus badge-style maps to a Qt style sheet applied to the badge.
    void setBadgeStyle(const QString &styleSheet);
    QString badgeStyle() const;

    // Positive x moves right; positive y moves down.
    void setOffset(const QPoint &offset);
    QPoint offset() const;

    // Element Plus badge-class maps to a Qt dynamic property.
    void setBadgeClass(const QString &className);
    QString badgeClass() const;

    // Maps Element Plus default slot. QelBadge takes ownership.
    void setContentWidget(QWidget *widget);
    QWidget *contentWidget() const;

    // Maps Element Plus content slot. QelBadge takes ownership.
    void setBadgeContentWidget(QWidget *widget);
    QWidget *badgeContentWidget() const;

    // Qt-native scoped-slot mapping. The renderer receives Element Plus'
    // computed content value (for example "99+") whenever it changes.
    void setBadgeContentRenderer(const BadgeContentRenderer &renderer);
    void clearBadgeContentRenderer();
    bool hasBadgeContentRenderer() const;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    void updateBadge();
    void updateRenderedBadgeContent();
    void updateChildGeometry();
    bool shouldShowBadge() const;
    bool isNumericValue() const;
    bool isZeroValue() const;

    QWidget *contentWidget_ = nullptr;
    QelBadgeBubble *bubble_ = nullptr;

    QVariant value_ = QString();
    double max_ = 99.0;
    bool dot_ = false;
    bool hidden_ = false;
    Type type_ = Type::Danger;
    bool showZero_ = true;

    QString color_;
    QString badgeStyle_;
    QString badgeClass_;
    QPoint offset_;
    BadgeContentRenderer badgeContentRenderer_;
};

} // namespace qel

#endif // QELBADGE_H
