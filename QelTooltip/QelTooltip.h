#ifndef QELTOOLTIP_H
#define QELTOOLTIP_H

#include <QFlags>
#include <QList>
#include <QObject>
#include <QPointer>
#include <QString>

class QEvent;
class QTimer;
class QWidget;

namespace qel {

class QelTooltipPopup;
class QelTooltipOutsideFilter;

class QelTooltip : public QObject
{
    Q_OBJECT

public:
    enum class Effect {
        Dark,
        Light
    };

    enum class Placement {
        TopStart,
        Top,
        TopEnd,
        BottomStart,
        Bottom,
        BottomEnd,
        LeftStart,
        Left,
        LeftEnd,
        RightStart,
        Right,
        RightEnd
    };

    enum class Trigger {
        Hover = 0x01,
        Focus = 0x02,
        Click = 0x04,
        ContextMenu = 0x08
    };
    Q_DECLARE_FLAGS(Triggers, Trigger)

    explicit QelTooltip(QWidget *target, QObject *parent = nullptr);
    ~QelTooltip() override;

    void setTarget(QWidget *target);
    QWidget *target() const;

    void setEffect(Effect effect);
    Effect effect() const;

    void setContent(const QString &content);
    QString content() const;

    void setRawContent(bool rawContent);
    bool rawContent() const;

    // Takes ownership of widget while it is used as tooltip content.
    // Pass nullptr to switch back to string content.
    void setContentWidget(QWidget *widget);
    QWidget *contentWidget() const;

    void setPlacement(Placement placement);
    Placement placement() const;

    void setFallbackPlacements(const QList<Placement> &placements);
    QList<Placement> fallbackPlacements() const;

    void setBoundariesPadding(int padding);
    int boundariesPadding() const;

    void setVisible(bool visible);
    bool isVisible() const;

    void setDisabled(bool disabled);
    bool isDisabled() const;

    void setOffset(int offset);
    int offset() const;

    void setTransition(const QString &transition);
    QString transition() const;

    void setShowArrow(bool show);
    bool showArrow() const;

    void setArrowOffset(int offset);
    int arrowOffset() const;

    void setShowAfter(int milliseconds);
    int showAfter() const;

    void setHideAfter(int milliseconds);
    int hideAfter() const;

    void setAutoClose(int milliseconds);
    int autoClose() const;

    void setTrigger(Trigger trigger);
    void setTriggers(Triggers triggers);
    Triggers triggers() const;

    void setTriggerKeys(const QList<int> &keys);
    QList<int> triggerKeys() const;

    void setFocusOnTarget(bool enabled);
    bool focusOnTarget() const;

    void setPersistent(bool persistent);
    bool isPersistent() const;

    void setPopperClass(const QString &className);
    QString popperClass() const;

    // Element Plus popper-style maps to Qt style sheet content.
    void setPopperStyle(const QString &styleSheet);
    QString popperStyle() const;

    void setEnterable(bool enterable);
    bool isEnterable() const;

    // Qt does not expose HTML tab order indexes directly. Non-negative
    // values make the target keyboard-focusable; negative disables focus.
    void setTabIndex(int tabIndex);
    int tabIndex() const;

public slots:
    void show();
    void hide();
    void toggle();

signals:
    void beforeShow();
    void beforeHide();
    void shown();
    void hidden();
    void visibilityChanged(bool visible);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void attachTarget(QWidget *target);
    void restoreTargetFocusPolicy();

    void ensurePopup();
    void updatePopup();
    void positionPopup();
    void destroyPopupIfInactive();

    void requestShow();
    void requestHide();
    void showNow();
    void hideNow();

    bool hasTrigger(Trigger trigger) const;
    bool useFadeTransition() const;

    QPointer<QWidget> target_;
    QPointer<QWidget> targetWindow_;
    QelTooltipPopup *popup_ = nullptr;
    QelTooltipOutsideFilter *outsideFilter_ = nullptr;

    QTimer *showTimer_ = nullptr;
    QTimer *hideTimer_ = nullptr;
    QTimer *autoCloseTimer_ = nullptr;

    Effect effect_ = Effect::Dark;
    QString content_;
    QPointer<QWidget> contentWidget_;
    Placement placement_ = Placement::Bottom;
    QList<Placement> fallbackPlacements_;

    Triggers triggers_ = Trigger::Hover;
    QList<int> triggerKeys_;

    bool rawContent_ = false;
    bool visible_ = false;
    bool disabled_ = false;
    bool showArrow_ = true;
    bool enterable_ = true;
    bool focusOnTarget_ = false;
    bool persistent_ = false;

    int offset_ = 12;
    int arrowOffset_ = 5;
    int showAfter_ = 0;
    int hideAfter_ = 200;
    int autoClose_ = 0;
    int boundariesPadding_ = 0;
    int tabIndex_ = 0;

    QString transition_ = "el-fade-in-linear";
    QString popperClass_;
    QString popperStyle_;

    Qt::FocusPolicy originalFocusPolicy_ = Qt::NoFocus;
    bool hasOriginalFocusPolicy_ = false;
};

} // namespace qel

Q_DECLARE_OPERATORS_FOR_FLAGS(qel::QelTooltip::Triggers)

#endif // QELTOOLTIP_H
