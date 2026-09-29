#ifndef QELTOOLTIPTESTER_H
#define QELTOOLTIPTESTER_H

#include "QelTooltip.h"

#include "../QelButton/QelButton.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

using qel::QelButton;
using qel::QelTooltip;

class QelTooltipTester : public QWidget
{
public:
    explicit QelTooltipTester(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(18);

        QLabel *title = new QLabel("Tooltip", this);
        title->setStyleSheet(
            "font-size: 28px; font-weight: 700; color: #303133;");
        mainLayout->addWidget(title);

        QLabel *description = new QLabel(
            "Element Plus aligned tooltip API and interaction behavior.",
            this);
        description->setStyleSheet("font-size: 14px; color: #606266;");
        mainLayout->addWidget(description);

        mainLayout->addWidget(createPlacementGroup());
        mainLayout->addWidget(createThemeGroup());
        mainLayout->addWidget(createTriggerGroup());
        mainLayout->addWidget(createAdvancedGroup());
        mainLayout->addStretch();
    }

private:
    QelButton *createTooltipButton(
        const QString &text,
        QelTooltip::Placement placement,
        QelTooltip::Effect effect = QelTooltip::Effect::Dark)
    {
        QelButton *button = new QelButton(
            QelButton::Default,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            text,
            this);
        button->setMinimumWidth(110);

        QelTooltip *tooltip = new QelTooltip(button, button);
        tooltip->setContent(QString("%1 prompts info").arg(text));
        tooltip->setPlacement(placement);
        tooltip->setEffect(effect);

        return button;
    }

    QGroupBox *createPlacementGroup()
    {
        QGroupBox *group = new QGroupBox("Placement", this);
        QGridLayout *grid = new QGridLayout(group);
        grid->setHorizontalSpacing(10);
        grid->setVerticalSpacing(10);

        grid->addWidget(
            createTooltipButton("top-start", QelTooltip::Placement::TopStart),
            0,
            1);
        grid->addWidget(
            createTooltipButton("top", QelTooltip::Placement::Top),
            0,
            2);
        grid->addWidget(
            createTooltipButton("top-end", QelTooltip::Placement::TopEnd),
            0,
            3);

        grid->addWidget(
            createTooltipButton("left-start", QelTooltip::Placement::LeftStart),
            1,
            0);
        grid->addWidget(
            createTooltipButton("right-start", QelTooltip::Placement::RightStart),
            1,
            4);

        grid->addWidget(
            createTooltipButton("left", QelTooltip::Placement::Left),
            2,
            0);

        QLabel *center = new QLabel("Hover each button", group);
        center->setAlignment(Qt::AlignCenter);
        center->setStyleSheet("color: #909399;");
        grid->addWidget(center, 1, 1, 3, 3);

        grid->addWidget(
            createTooltipButton("right", QelTooltip::Placement::Right),
            2,
            4);

        grid->addWidget(
            createTooltipButton("left-end", QelTooltip::Placement::LeftEnd),
            3,
            0);
        grid->addWidget(
            createTooltipButton("right-end", QelTooltip::Placement::RightEnd),
            3,
            4);

        grid->addWidget(
            createTooltipButton(
                "bottom-start",
                QelTooltip::Placement::BottomStart),
            4,
            1);
        grid->addWidget(
            createTooltipButton("bottom", QelTooltip::Placement::Bottom),
            4,
            2);
        grid->addWidget(
            createTooltipButton("bottom-end", QelTooltip::Placement::BottomEnd),
            4,
            3);

        return group;
    }

    QGroupBox *createThemeGroup()
    {
        QGroupBox *group = new QGroupBox("Theme and content", this);
        QHBoxLayout *layout = new QHBoxLayout(group);

        layout->addWidget(
            createTooltipButton("Dark", QelTooltip::Placement::Top));

        layout->addWidget(
            createTooltipButton(
                "Light",
                QelTooltip::Placement::Bottom,
                QelTooltip::Effect::Light));

        QelButton *rawButton = new QelButton(
            QelButton::Primary,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Raw content",
            this);
        QelTooltip *rawTooltip = new QelTooltip(rawButton, rawButton);
        rawTooltip->setContent("<b>bold</b><br/>second line");
        rawTooltip->setRawContent(true);
        rawTooltip->setPlacement(QelTooltip::Placement::Top);
        layout->addWidget(rawButton);

        QelButton *customButton = new QelButton(
            QelButton::Primary,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Custom QWidget",
            this);
        QelTooltip *customTooltip =
            new QelTooltip(customButton, customButton);
        customTooltip->setPlacement(QelTooltip::Placement::Top);
        QLabel *customContent =
            new QLabel("multiple lines\nsecond line");
        customTooltip->setContentWidget(customContent);
        layout->addWidget(customButton);

        layout->addStretch();
        return group;
    }

    QGroupBox *createTriggerGroup()
    {
        QGroupBox *group = new QGroupBox("Trigger", this);
        QHBoxLayout *layout = new QHBoxLayout(group);

        QelButton *hoverButton = new QelButton(
            QelButton::Default,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Hover",
            this);
        QelTooltip *hoverTooltip =
            new QelTooltip(hoverButton, hoverButton);
        hoverTooltip->setContent("trigger = hover");
        layout->addWidget(hoverButton);

        QelButton *clickButton = new QelButton(
            QelButton::Default,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Click",
            this);
        QelTooltip *clickTooltip =
            new QelTooltip(clickButton, clickButton);
        clickTooltip->setContent("trigger = click");
        clickTooltip->setTrigger(QelTooltip::Trigger::Click);
        layout->addWidget(clickButton);

        QelButton *focusButton = new QelButton(
            QelButton::Default,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Focus",
            this);
        QelTooltip *focusTooltip =
            new QelTooltip(focusButton, focusButton);
        focusTooltip->setContent("trigger = focus");
        focusTooltip->setTrigger(QelTooltip::Trigger::Focus);
        layout->addWidget(focusButton);

        QelButton *contextButton = new QelButton(
            QelButton::Default,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Context menu",
            this);
        QelTooltip *contextTooltip =
            new QelTooltip(contextButton, contextButton);
        contextTooltip->setContent("trigger = contextmenu");
        contextTooltip->setTrigger(QelTooltip::Trigger::ContextMenu);
        layout->addWidget(contextButton);

        QelButton *mixedButton = new QelButton(
            QelButton::Default,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Hover + Focus",
            this);
        QelTooltip *mixedTooltip =
            new QelTooltip(mixedButton, mixedButton);
        mixedTooltip->setContent("trigger = hover + focus");
        mixedTooltip->setTriggers(
            QelTooltip::Trigger::Hover
            | QelTooltip::Trigger::Focus);
        layout->addWidget(mixedButton);

        layout->addStretch();
        return group;
    }

    QGroupBox *createAdvancedGroup()
    {
        QGroupBox *group = new QGroupBox("Advanced usage", this);
        QVBoxLayout *layout = new QVBoxLayout(group);

        QHBoxLayout *timingRow = new QHBoxLayout();

        QelButton *showAfterButton = new QelButton(
            QelButton::Default,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Show after 800ms",
            this);
        QelTooltip *showAfterTooltip =
            new QelTooltip(showAfterButton, showAfterButton);
        showAfterTooltip->setContent("show-after = 800");
        showAfterTooltip->setShowAfter(800);
        timingRow->addWidget(showAfterButton);

        QelButton *hideAfterButton = new QelButton(
            QelButton::Default,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Hide after 800ms",
            this);
        QelTooltip *hideAfterTooltip =
            new QelTooltip(hideAfterButton, hideAfterButton);
        hideAfterTooltip->setContent("hide-after = 800");
        hideAfterTooltip->setHideAfter(800);
        timingRow->addWidget(hideAfterButton);

        QelButton *autoCloseButton = new QelButton(
            QelButton::Default,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Auto close 1500ms",
            this);
        QelTooltip *autoCloseTooltip =
            new QelTooltip(autoCloseButton, autoCloseButton);
        autoCloseTooltip->setContent("auto-close = 1500");
        autoCloseTooltip->setAutoClose(1500);
        timingRow->addWidget(autoCloseButton);

        timingRow->addStretch();
        layout->addLayout(timingRow);

        QHBoxLayout *optionsRow = new QHBoxLayout();

        QelButton *noArrowButton = new QelButton(
            QelButton::Default,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "No arrow",
            this);
        QelTooltip *noArrowTooltip =
            new QelTooltip(noArrowButton, noArrowButton);
        noArrowTooltip->setContent("show-arrow = false");
        noArrowTooltip->setShowArrow(false);
        optionsRow->addWidget(noArrowButton);

        QelButton *fallbackButton = new QelButton(
            QelButton::Default,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Fallback",
            this);
        QelTooltip *fallbackTooltip =
            new QelTooltip(fallbackButton, fallbackButton);
        fallbackTooltip->setContent("fallback placements");
        fallbackTooltip->setPlacement(QelTooltip::Placement::Top);
        fallbackTooltip->setFallbackPlacements({
            QelTooltip::Placement::Bottom,
            QelTooltip::Placement::Right,
            QelTooltip::Placement::Left
        });
        optionsRow->addWidget(fallbackButton);

        QelButton *disabledButton = new QelButton(
            QelButton::Default,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Disabled",
            this);
        QelTooltip *disabledTooltip =
            new QelTooltip(disabledButton, disabledButton);
        disabledTooltip->setContent("You should not see this");
        disabledTooltip->setDisabled(true);
        optionsRow->addWidget(disabledButton);

        optionsRow->addStretch();
        layout->addLayout(optionsRow);

        QHBoxLayout *controlledRow = new QHBoxLayout();

        QelButton *controlledTarget = new QelButton(
            QelButton::Primary,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Controlled target",
            this);
        QelTooltip *controlledTooltip =
            new QelTooltip(controlledTarget, controlledTarget);
        controlledTooltip->setContent("Controlled with show()/hide()");
        controlledTooltip->setPlacement(QelTooltip::Placement::Right);
        controlledTooltip->setTriggers(QelTooltip::Triggers());

        QelButton *showButton = new QelButton(
            QelButton::Success,
            QelButton::SmallSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Show",
            this);

        QelButton *hideButton = new QelButton(
            QelButton::Danger,
            QelButton::SmallSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            "Hide",
            this);

        QObject::connect(
            showButton,
            &QPushButton::clicked,
            controlledTooltip,
            &QelTooltip::show);
        QObject::connect(
            hideButton,
            &QPushButton::clicked,
            controlledTooltip,
            &QelTooltip::hide);

        controlledRow->addWidget(controlledTarget);
        controlledRow->addWidget(showButton);
        controlledRow->addWidget(hideButton);
        controlledRow->addStretch();
        layout->addLayout(controlledRow);

        return group;
    }
};

#endif // QELTOOLTIPTESTER_H
