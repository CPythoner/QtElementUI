#ifndef QELPROGRESS_H
#define QELPROGRESS_H

#include <functional>

#include <QElapsedTimer>
#include <QString>
#include <QVector>
#include <QWidget>

class QHideEvent;
class QPaintEvent;
class QPainter;
class QResizeEvent;
class QShowEvent;
class QTimer;

namespace qel {

class QelProgress : public QWidget
{
    Q_OBJECT

public:
    enum class Type {
        Line,
        Circle,
        Dashboard
    };

    enum class Status {
        Normal,
        Success,
        Exception,
        Warning
    };

    enum class StrokeLinecap {
        Butt,
        Round,
        Square
    };

    struct ProgressColor {
        QString color;
        double percentage = 100.0;
    };

    using ColorFunction = std::function<QString(double percentage)>;
    using FormatFunction = std::function<QString(double percentage)>;
    using ContentRenderer =
        std::function<QWidget *(double percentage, QWidget *parent)>;

    explicit QelProgress(QWidget *parent = nullptr);
    ~QelProgress() override;

    void setType(Type type);
    Type type() const;

    void setPercentage(double percentage);
    double percentage() const;

    void setStatus(Status status);
    Status status() const;

    void setIndeterminate(bool indeterminate);
    bool isIndeterminate() const;

    void setDuration(double seconds);
    double duration() const;

    void setStrokeWidth(int width);
    int strokeWidth() const;

    void setStrokeLinecap(StrokeLinecap linecap);
    StrokeLinecap strokeLinecap() const;

    void setTextInside(bool textInside);
    bool textInside() const;

    void setWidth(int width);
    int progressWidth() const;

    void setShowText(bool show);
    bool showText() const;

    void setColor(const QString &color);
    QString color() const;

    void setColors(const QVector<ProgressColor> &colors);
    QVector<ProgressColor> colors() const;

    void setColorFunction(const ColorFunction &function);
    bool hasColorFunction() const;

    void clearColor();

    void setStriped(bool striped);
    bool isStriped() const;

    void setStripedFlow(bool flow);
    bool stripedFlow() const;

    void setFormat(const FormatFunction &format);
    void clearFormat();
    QString formattedText() const;

    // Maps the Element Plus default scoped slot.
    void setContentRenderer(const ContentRenderer &renderer);
    void clearContentRenderer();
    bool hasContentRenderer() const;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

private:
    void paintLine(QPainter &painter);
    void paintCircle(QPainter &painter, bool dashboard);
    void paintDefaultText(QPainter &painter, const QRectF &rect);

    void updateAnimationState();
    void updateContentWidget();
    void updateContentGeometry();

    QRectF lineTrackRect() const;
    QRectF circularRect() const;
    QString currentColor() const;
    QString statusColor() const;
    Qt::PenCapStyle qtCapStyle() const;
    double animationPhase() const;
    double visualPercentage() const;

    Type type_ = Type::Line;
    double percentage_ = 0.0;
    Status status_ = Status::Normal;
    bool indeterminate_ = false;
    double duration_ = 3.0;
    int strokeWidth_ = 6;
    StrokeLinecap strokeLinecap_ = StrokeLinecap::Round;
    bool textInside_ = false;
    int width_ = 126;
    bool showText_ = true;

    QString color_;
    QVector<ProgressColor> colors_;
    ColorFunction colorFunction_;

    bool striped_ = false;
    bool stripedFlow_ = false;

    FormatFunction format_;
    ContentRenderer contentRenderer_;
    QWidget *contentWidget_ = nullptr;

    QTimer *animationTimer_ = nullptr;
    QElapsedTimer animationClock_;

    double transitionStartPercentage_ = 0.0;
    bool transitionActive_ = false;
    QElapsedTimer transitionClock_;
};

} // namespace qel

#endif // QELPROGRESS_H
