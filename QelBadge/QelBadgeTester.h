#ifndef QELBADGETESTER_H
#define QELBADGETESTER_H

#include "QelBadge.h"

#include "../QelButton/QelButton.h"
#include "../QelIcon/QelIcon.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QWidgetAction>

using qel::QelBadge;
using qel::QelButton;
using qel::QelIcon;

class QelBadgeTester : public QWidget
{
public:
    explicit QelBadgeTester(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(18);

        QLabel *title = new QLabel("Badge", this);
        title->setStyleSheet(
            "font-size: 28px; font-weight: 700; color: #303133;");
        mainLayout->addWidget(title);

        QLabel *description = new QLabel(
            "Element Plus 2.14.6 official Badge examples mapped to Qt.",
            this);
        description->setStyleSheet("font-size: 14px; color: #606266;");
        mainLayout->addWidget(description);

        mainLayout->addWidget(createBasicGroup());
        mainLayout->addWidget(createMaxGroup());
        mainLayout->addWidget(createCustomContentGroup());
        mainLayout->addWidget(createDotGroup());
        mainLayout->addWidget(createOffsetGroup());
        mainLayout->addStretch();
    }

private:
    QelButton *makeButton(const QString &text,
                          QelButton::ButtonType type = QelButton::Default)
    {
        return new QelButton(
            type,
            QelButton::DefaultSize,
            false,
            false,
            false,
            false,
            QelButton::Button,
            QIcon(),
            text,
            this);
    }

    QelBadge *makeButtonBadge(const QString &text, const QVariant &value)
    {
        QelBadge *badge = new QelBadge(this);
        badge->setContentWidget(makeButton(text));
        badge->setValue(value);
        return badge;
    }

    QWidget *makeDropdownDemo()
    {
        QToolButton *dropdown = new QToolButton(this);
        dropdown->setText("Click Me  ▾");
        dropdown->setPopupMode(QToolButton::InstantPopup);
        dropdown->setAutoRaise(true);

        QMenu *menu = new QMenu(dropdown);

        auto addRow = [menu](const QString &text, int value) {
            QWidget *row = new QWidget(menu);
            QHBoxLayout *rowLayout = new QHBoxLayout(row);
            rowLayout->setContentsMargins(10, 4, 10, 4);

            QLabel *label = new QLabel(text, row);
            QelBadge *mark = new QelBadge(row);
            mark->setValue(value);

            rowLayout->addWidget(label);
            rowLayout->addStretch();
            rowLayout->addWidget(mark);

            QWidgetAction *action = new QWidgetAction(menu);
            action->setDefaultWidget(row);
            menu->addAction(action);
        };

        addRow("comments", 12);
        addRow("replies", 3);

        dropdown->setMenu(menu);
        return dropdown;
    }

    QGroupBox *createBasicGroup()
    {
        QGroupBox *group = new QGroupBox("Basic", this);
        QHBoxLayout *layout = new QHBoxLayout(group);

        layout->addWidget(makeButtonBadge("comments", 12));
        layout->addWidget(makeButtonBadge("replies", 3));

        QelBadge *primary = makeButtonBadge("comments", 1);
        primary->setType(QelBadge::Primary);
        layout->addWidget(primary);

        QelBadge *warning = makeButtonBadge("replies", 2);
        warning->setType(QelBadge::Warning);
        layout->addWidget(warning);

        QelBadge *custom = makeButtonBadge("custom background", 1);
        custom->setColor("green");
        layout->addWidget(custom);

        layout->addWidget(makeDropdownDemo());
        layout->addStretch();

        return group;
    }

    QGroupBox *createMaxGroup()
    {
        QGroupBox *group = new QGroupBox("Max value", this);
        QHBoxLayout *layout = new QHBoxLayout(group);

        QelBadge *comments = makeButtonBadge("comments", 200);
        comments->setMax(99);
        layout->addWidget(comments);

        QelBadge *replies = makeButtonBadge("replies", 100);
        replies->setMax(10);
        layout->addWidget(replies);

        layout->addStretch();
        return group;
    }

    QGroupBox *createCustomContentGroup()
    {
        QGroupBox *group = new QGroupBox("Custom content", this);
        QHBoxLayout *layout = new QHBoxLayout(group);

        layout->addWidget(makeButtonBadge("comments", QString("new")));
        layout->addWidget(makeButtonBadge("replies", QString("hot")));

        QelBadge *share = makeButtonBadge("share", 99);
        share->setBadgeContentRenderer(
            [](const QString &value, QWidget *parent) -> QWidget * {
                QWidget *content = new QWidget(parent);
                QHBoxLayout *contentLayout = new QHBoxLayout(content);
                contentLayout->setContentsMargins(0, 0, 0, 0);
                contentLayout->setSpacing(4);

                QLabel *icon = new QLabel(content);
                icon->setPixmap(
                    QelIcon(QelIcon::Envelope, 12, Qt::white)
                        .pixmap(12, 12));
                icon->setFixedSize(12, 12);

                QLabel *valueLabel = new QLabel(value, content);
                valueLabel->setStyleSheet(
                    "color: white; background: transparent; font-size: 12px;");

                contentLayout->addWidget(icon);
                contentLayout->addWidget(valueLabel);
                return content;
            });
        layout->addWidget(share);

        layout->addStretch();
        return group;
    }

    QGroupBox *createDotGroup()
    {
        QGroupBox *group = new QGroupBox("Dot", this);
        QHBoxLayout *layout = new QHBoxLayout(group);

        QelBadge *query = new QelBadge(this);
        QLabel *queryText = new QLabel("query", this);
        queryText->setMinimumSize(56, 32);
        queryText->setAlignment(Qt::AlignCenter);
        query->setContentWidget(queryText);
        query->setDot(true);
        layout->addWidget(query);

        QelBadge *share = new QelBadge(this);
        QelButton *shareButton = makeButton("Share", QelButton::Primary);
        share->setContentWidget(shareButton);
        share->setDot(true);
        layout->addWidget(share);

        layout->addStretch();
        return group;
    }

    QGroupBox *createOffsetGroup()
    {
        QGroupBox *group = new QGroupBox("Offset", this);
        QHBoxLayout *layout = new QHBoxLayout(group);

        QelBadge *offset = makeButtonBadge("offset", 1);
        offset->setOffset(QPoint(10, 5));
        layout->addWidget(offset);

        QLabel *description = new QLabel(
            "offset = [10, 5]  →  right 10px, down 5px",
            group);
        description->setStyleSheet("color: #606266;");
        layout->addWidget(description);
        layout->addStretch();

        return group;
    }
};

#endif // QELBADGETESTER_H
