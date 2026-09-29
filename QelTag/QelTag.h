#ifndef QELTAG_H
#define QELTAG_H

#include <QString>
#include <QWidget>

#include "../QelCommon/QelControlTypes.h"

class QLabel;
class QToolButton;
class QHBoxLayout;
class QMouseEvent;
class QPaintEvent;
class QShowEvent;

namespace qel {

class QelTag : public QWidget
{
    Q_OBJECT

public:
    using Size = QelControlSize;

    enum class Type {
        Primary,
        Success,
        Info,
        Warning,
        Danger
    };

    enum class Effect {
        Dark,
        Light,
        Plain
    };

    static constexpr Type Primary = Type::Primary;
    static constexpr Type Success = Type::Success;
    static constexpr Type Info = Type::Info;
    static constexpr Type Warning = Type::Warning;
    static constexpr Type Danger = Type::Danger;

    static constexpr Size Large = Size::Large;
    static constexpr Size Default = Size::Default;
    static constexpr Size Small = Size::Small;

    explicit QelTag(const QString &text = QString(),
                    Type type = Type::Primary,
                    Size size = Size::Default,
                    Effect effect = Effect::Light,
                    QWidget *parent = nullptr);

    void setText(const QString &text);
    QString text() const;

    void setType(Type type);
    Type type() const;

    void setClosable(bool closable);
    bool isClosable() const;

    void setDisableTransitions(bool disabled);
    bool transitionsDisabled() const;

    void setHit(bool hit);
    bool isHit() const;

    void setColor(const QString &color);
    QString color() const;

    void setSize(Size size);
    Size size() const;

    void setEffect(Effect effect);
    Effect effect() const;

    void setRound(bool round);
    bool isRound() const;

signals:
    void closeRequested();
    void clicked();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    void updateStyle();
    void updateLayoutMetrics();

    QLabel *label_ = nullptr;
    QToolButton *closeButton_ = nullptr;
    QHBoxLayout *layout_ = nullptr;

    Type type_ = Type::Primary;
    Size size_ = Size::Default;
    Effect effect_ = Effect::Light;

    bool closable_ = false;
    bool disableTransitions_ = false;
    bool hit_ = false;
    bool round_ = false;
    bool transitionPlayed_ = false;

    QString color_;
    QString backgroundColor_;
    QString borderColor_;
};

} // namespace qel

#endif // QELTAG_H
