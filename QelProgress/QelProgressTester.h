#ifndef QELPROGRESSTESTER_H
#define QELPROGRESSTESTER_H

#include "QelProgress.h"

#include "../QelButton/QelButton.h"
#include "../QelIcon/QelIcon.h"

#include <QFrame>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include <cmath>

using qel::QelButton;
using qel::QelIcon;
using qel::QelProgress;

class QelProgressTester : public QWidget
{
public:
    explicit QelProgressTester(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        QVBoxLayout *rootLayout = new QVBoxLayout(this);
        rootLayout->setContentsMargins(0, 0, 0, 0);

        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setWidgetResizable(true);
        scrollArea->setFrameShape(QFrame::NoFrame);
        rootLayout->addWidget(scrollArea);

        QWidget *content = new QWidget(scrollArea);
        QVBoxLayout *mainLayout = new QVBoxLayout(content);
        mainLayout->setSpacing(18);

        QLabel *title = new QLabel("Progress", content);
        title->setStyleSheet(
            "font-size: 28px; font-weight: 700; color: #303133;");
        mainLayout->addWidget(title);

        QLabel *description = new QLabel(
            "Element Plus 2.14.6 official Progress examples mapped to Qt.",
            content);
        description->setStyleSheet("font-size: 14px; color: #606266;");
        mainLayout->addWidget(description);

        mainLayout->addWidget(createLinearGroup(content));
        mainLayout->addWidget(createInternalGroup(content));
        mainLayout->addWidget(createCustomColorGroup(content));
        mainLayout->addWidget(createCustomContentGroup(content));
        mainLayout->addWidget(createCircleGroup(content));
        mainLayout->addWidget(createDashboardGroup(content));
        mainLayout->addWidget(createIndeterminateGroup(content));
        mainLayout->addWidget(createStripedGroup(content));
        mainLayout->addStretch();

        scrollArea->setWidget(content);
    }

private:
    QelProgress *makeLine(double percentage, QWidget *parent)
    {
        QelProgress *progress = new QelProgress(parent);
        progress->setPercentage(percentage);
        progress->setMinimumWidth(420);
        return progress;
    }

    QelButton *makeIconButton(QelIcon::Icon icon, QWidget *parent)
    {
        QelButton *button = new QelButton(
            QelButton::Default,
            QelButton::SmallSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QelIcon(icon, 14),
            QString(),
            parent);
        button->setFixedWidth(36);
        return button;
    }

    QWidget *makeControls(
        QelProgress *progress,
        QWidget *parent,
        const std::function<void(double)> &afterChange = {})
    {
        QWidget *controls = new QWidget(parent);
        QHBoxLayout *layout = new QHBoxLayout(controls);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        QelButton *minus = makeIconButton(QelIcon::Minus, controls);
        QelButton *plus = makeIconButton(QelIcon::Plus, controls);

        QObject::connect(
            minus,
            &QPushButton::clicked,
            progress,
            [progress, afterChange]() {
                const double value =
                    qMax(0.0, progress->percentage() - 10.0);
                progress->setPercentage(value);
                if (afterChange) {
                    afterChange(value);
                }
            });

        QObject::connect(
            plus,
            &QPushButton::clicked,
            progress,
            [progress, afterChange]() {
                const double value =
                    qMin(100.0, progress->percentage() + 10.0);
                progress->setPercentage(value);
                if (afterChange) {
                    afterChange(value);
                }
            });

        layout->addWidget(minus);
        layout->addWidget(plus);
        layout->addStretch();
        return controls;
    }

    QGroupBox *createLinearGroup(QWidget *parent)
    {
        QGroupBox *group = new QGroupBox("Linear progress bar", parent);
        QVBoxLayout *layout = new QVBoxLayout(group);

        layout->addWidget(makeLine(50, group));

        QelProgress *full = makeLine(100, group);
        full->setFormat([](double percentage) {
            return percentage >= 100.0
                ? QString("Full")
                : QString::number(percentage, 'g', 15) + "%";
        });
        layout->addWidget(full);

        QelProgress *success = makeLine(100, group);
        success->setStatus(QelProgress::Status::Success);
        layout->addWidget(success);

        QelProgress *warning = makeLine(100, group);
        warning->setStatus(QelProgress::Status::Warning);
        layout->addWidget(warning);

        QelProgress *exception = makeLine(50, group);
        exception->setStatus(QelProgress::Status::Exception);
        layout->addWidget(exception);

        return group;
    }

    QGroupBox *createInternalGroup(QWidget *parent)
    {
        QGroupBox *group = new QGroupBox("Internal percentage", parent);
        QVBoxLayout *layout = new QVBoxLayout(group);

        QelProgress *normal = makeLine(70, group);
        normal->setTextInside(true);
        normal->setStrokeWidth(26);
        layout->addWidget(normal);

        QelProgress *success = makeLine(100, group);
        success->setTextInside(true);
        success->setStrokeWidth(24);
        success->setStatus(QelProgress::Status::Success);
        layout->addWidget(success);

        QelProgress *warning = makeLine(80, group);
        warning->setTextInside(true);
        warning->setStrokeWidth(22);
        warning->setStatus(QelProgress::Status::Warning);
        layout->addWidget(warning);

        QelProgress *exception = makeLine(50, group);
        exception->setTextInside(true);
        exception->setStrokeWidth(20);
        exception->setStatus(QelProgress::Status::Exception);
        layout->addWidget(exception);

        return group;
    }

    QGroupBox *createCustomColorGroup(QWidget *parent)
    {
        QGroupBox *group = new QGroupBox("Custom color", parent);
        QVBoxLayout *layout = new QVBoxLayout(group);

        QelProgress *staticColor = makeLine(20, group);
        staticColor->setColor("#409EFF");
        layout->addWidget(staticColor);

        QelProgress *functionColor = makeLine(20, group);
        functionColor->setColorFunction([](double percentage) {
            if (percentage < 30.0) {
                return QString("#909399");
            }
            if (percentage < 70.0) {
                return QString("#E6A23C");
            }
            return QString("#67C23A");
        });
        layout->addWidget(functionColor);

        const QVector<QelProgress::ProgressColor> colors = {
            {"#F56C6C", 20},
            {"#E6A23C", 40},
            {"#5CB87A", 60},
            {"#1989FA", 80},
            {"#6F7AD3", 100}
        };

        QelProgress *series = makeLine(20, group);
        series->setColors(colors);
        layout->addWidget(series);

        QelProgress *series2 = makeLine(20, group);
        series2->setColors(colors);
        layout->addWidget(series2);

        QWidget *controls = makeControls(
            series,
            group,
            [staticColor, functionColor, series2](double value) {
                staticColor->setPercentage(value);
                functionColor->setPercentage(value);
                series2->setPercentage(value);
            });
        layout->addWidget(controls);

        return group;
    }

    QGroupBox *createCustomContentGroup(QWidget *parent)
    {
        QGroupBox *group = new QGroupBox("Customized content", parent);
        QVBoxLayout *layout = new QVBoxLayout(group);

        QelProgress *line = makeLine(50, group);
        line->setContentRenderer(
            [](double, QWidget *contentParent) -> QWidget * {
                QelButton *button = new QelButton(
                    QelButton::Default,
                    QelButton::SmallSize,
                    false,
                    false,
                    false,
                    false,
                    QelButton::Button,
                    QIcon(),
                    "Content",
                    contentParent);
                button->setTextMode(true);
                return button;
            });
        layout->addWidget(line);

        QelProgress *inside = makeLine(50, group);
        inside->setTextInside(true);
        inside->setStrokeWidth(20);
        inside->setStatus(QelProgress::Status::Exception);
        inside->setContentRenderer(
            [](double, QWidget *contentParent) -> QWidget * {
                QLabel *label = new QLabel("Content", contentParent);
                label->setStyleSheet(
                    "color: white; background: transparent; font-size: 12px;");
                return label;
            });
        layout->addWidget(inside);

        QWidget *circleRow = new QWidget(group);
        QHBoxLayout *circleLayout = new QHBoxLayout(circleRow);
        circleLayout->setContentsMargins(0, 0, 0, 0);

        QelProgress *circle = new QelProgress(circleRow);
        circle->setType(QelProgress::Type::Circle);
        circle->setPercentage(100);
        circle->setStatus(QelProgress::Status::Success);
        circle->setContentRenderer(
            [](double, QWidget *contentParent) -> QWidget * {
                QelButton *button = new QelButton(
                    QelButton::Success,
                    QelButton::SmallSize,
                    false,
                    false,
                    true,
                    false,
                    QelButton::Button,
                    QelIcon(QelIcon::Check, 14, Qt::white),
                    QString(),
                    contentParent);
                button->setFixedSize(32, 32);
                return button;
            });
        circleLayout->addWidget(circle);

        QelProgress *dashboard = new QelProgress(circleRow);
        dashboard->setType(QelProgress::Type::Dashboard);
        dashboard->setPercentage(80);
        dashboard->setContentRenderer(
            [](double percentage, QWidget *contentParent) -> QWidget * {
                QWidget *content = new QWidget(contentParent);
                QVBoxLayout *contentLayout = new QVBoxLayout(content);
                contentLayout->setContentsMargins(0, 0, 0, 0);
                contentLayout->setSpacing(4);

                QLabel *value = new QLabel(
                    QString::number(percentage, 'g', 15) + "%",
                    content);
                value->setAlignment(Qt::AlignCenter);
                value->setStyleSheet(
                    "font-size: 22px; color: #303133;");

                QLabel *label = new QLabel("Progressing", content);
                label->setAlignment(Qt::AlignCenter);
                label->setStyleSheet(
                    "font-size: 12px; color: #909399;");

                contentLayout->addWidget(value);
                contentLayout->addWidget(label);
                return content;
            });
        circleLayout->addWidget(dashboard);
        circleLayout->addStretch();

        layout->addWidget(circleRow);
        return group;
    }

    QGroupBox *createCircleGroup(QWidget *parent)
    {
        QGroupBox *group = new QGroupBox("Circular progress bar", parent);
        QHBoxLayout *layout = new QHBoxLayout(group);

        const struct {
            double percentage;
            QelProgress::Status status;
        } items[] = {
            {0, QelProgress::Status::Normal},
            {25, QelProgress::Status::Normal},
            {100, QelProgress::Status::Success},
            {70, QelProgress::Status::Warning},
            {50, QelProgress::Status::Exception}
        };

        for (const auto &item : items) {
            QelProgress *progress = new QelProgress(group);
            progress->setType(QelProgress::Type::Circle);
            progress->setPercentage(item.percentage);
            progress->setStatus(item.status);
            layout->addWidget(progress);
        }

        layout->addStretch();
        return group;
    }

    QGroupBox *createDashboardGroup(QWidget *parent)
    {
        QGroupBox *group = new QGroupBox("Dashboard progress bar", parent);
        QVBoxLayout *layout = new QVBoxLayout(group);

        QWidget *row = new QWidget(group);
        QHBoxLayout *rowLayout = new QHBoxLayout(row);
        rowLayout->setContentsMargins(0, 0, 0, 0);

        const QVector<QelProgress::ProgressColor> colors = {
            {"#F56C6C", 20},
            {"#E6A23C", 40},
            {"#5CB87A", 60},
            {"#1989FA", 80},
            {"#6F7AD3", 100}
        };

        QelProgress *manual = new QelProgress(row);
        manual->setType(QelProgress::Type::Dashboard);
        manual->setPercentage(10);
        manual->setColors(colors);
        rowLayout->addWidget(manual);

        QelProgress *automatic = new QelProgress(row);
        automatic->setType(QelProgress::Type::Dashboard);
        automatic->setPercentage(0);
        automatic->setColors(colors);
        rowLayout->addWidget(automatic);
        rowLayout->addStretch();

        layout->addWidget(row);
        layout->addWidget(makeControls(manual, group));

        QTimer *timer = new QTimer(group);
        timer->setInterval(500);
        QObject::connect(timer, &QTimer::timeout, automatic, [automatic]() {
            const double next =
                std::fmod(automatic->percentage(), 100.0) + 10.0;
            automatic->setPercentage(next);
        });
        timer->start();

        return group;
    }

    QGroupBox *createIndeterminateGroup(QWidget *parent)
    {
        QGroupBox *group = new QGroupBox("Indeterminate progress", parent);
        QVBoxLayout *layout = new QVBoxLayout(group);

        QelProgress *p1 = makeLine(50, group);
        p1->setIndeterminate(true);
        layout->addWidget(p1);

        QelProgress *p2 = makeLine(100, group);
        p2->setFormat([](double percentage) {
            return percentage >= 100.0
                ? QString("Full")
                : QString::number(percentage, 'g', 15) + "%";
        });
        p2->setIndeterminate(true);
        layout->addWidget(p2);

        QelProgress *p3 = makeLine(100, group);
        p3->setStatus(QelProgress::Status::Success);
        p3->setIndeterminate(true);
        p3->setDuration(5);
        layout->addWidget(p3);

        QelProgress *p4 = makeLine(100, group);
        p4->setStatus(QelProgress::Status::Warning);
        p4->setIndeterminate(true);
        p4->setDuration(1);
        layout->addWidget(p4);

        QelProgress *p5 = makeLine(50, group);
        p5->setStatus(QelProgress::Status::Exception);
        p5->setIndeterminate(true);
        layout->addWidget(p5);

        return group;
    }

    QGroupBox *createStripedGroup(QWidget *parent)
    {
        QGroupBox *group = new QGroupBox("Striped progress", parent);
        QVBoxLayout *layout = new QVBoxLayout(group);

        QelProgress *p1 = makeLine(50, group);
        p1->setStrokeWidth(15);
        p1->setStriped(true);
        layout->addWidget(p1);

        QelProgress *p2 = makeLine(30, group);
        p2->setStrokeWidth(15);
        p2->setStatus(QelProgress::Status::Warning);
        p2->setStriped(true);
        p2->setStripedFlow(true);
        layout->addWidget(p2);

        QelProgress *p3 = makeLine(100, group);
        p3->setStrokeWidth(15);
        p3->setStatus(QelProgress::Status::Success);
        p3->setStriped(true);
        p3->setStripedFlow(true);
        p3->setDuration(10);
        layout->addWidget(p3);

        QelProgress *p4 = makeLine(70, group);
        p4->setStrokeWidth(15);
        p4->setStatus(QelProgress::Status::Exception);
        p4->setStriped(true);
        p4->setStripedFlow(true);
        p4->setDuration(7);
        layout->addWidget(p4);

        layout->addWidget(
            makeControls(
                p4,
                group,
                [p4](double value) {
                    p4->setDuration(std::floor(value / 10.0));
                }));

        return group;
    }
};

#endif // QELPROGRESSTESTER_H
