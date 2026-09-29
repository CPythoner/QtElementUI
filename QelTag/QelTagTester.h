#ifndef QELTAGTESTER_H
#define QELTAGTESTER_H

#include "QelTag.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

using qel::QelTag;

class QelTagTester : public QWidget
{
public:
    explicit QelTagTester(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(18);

        QLabel *title = new QLabel("Tag", this);
        title->setStyleSheet(
            "font-size: 28px; font-weight: 700; color: #303133;");
        mainLayout->addWidget(title);

        QLabel *description = new QLabel(
            "Element Plus 2.14.6 aligned tag variants and behavior.",
            this);
        description->setStyleSheet("font-size: 14px; color: #606266;");
        mainLayout->addWidget(description);

        mainLayout->addWidget(createTypesGroup());
        mainLayout->addWidget(createEffectsGroup());
        mainLayout->addWidget(createSizesGroup());
        mainLayout->addWidget(createOptionsGroup());
        mainLayout->addWidget(createEventsGroup());
        mainLayout->addStretch();
    }

private:
    QelTag *makeTag(const QString &text,
                    QelTag::Type type = QelTag::Primary,
                    QelTag::Size size = QelTag::Default,
                    QelTag::Effect effect = QelTag::Effect::Light)
    {
        return new QelTag(text, type, size, effect, this);
    }

    QGroupBox *createTypesGroup()
    {
        QGroupBox *group = new QGroupBox("Type", this);
        QHBoxLayout *layout = new QHBoxLayout(group);

        layout->addWidget(makeTag("Primary", QelTag::Primary));
        layout->addWidget(makeTag("Success", QelTag::Success));
        layout->addWidget(makeTag("Info", QelTag::Info));
        layout->addWidget(makeTag("Warning", QelTag::Warning));
        layout->addWidget(makeTag("Danger", QelTag::Danger));
        layout->addStretch();

        return group;
    }

    QGroupBox *createEffectsGroup()
    {
        QGroupBox *group = new QGroupBox("Effect", this);
        QHBoxLayout *layout = new QHBoxLayout(group);

        layout->addWidget(
            makeTag("Light", QelTag::Primary, QelTag::Default,
                    QelTag::Effect::Light));
        layout->addWidget(
            makeTag("Dark", QelTag::Success, QelTag::Default,
                    QelTag::Effect::Dark));
        layout->addWidget(
            makeTag("Plain", QelTag::Warning, QelTag::Default,
                    QelTag::Effect::Plain));
        layout->addStretch();

        return group;
    }

    QGroupBox *createSizesGroup()
    {
        QGroupBox *group = new QGroupBox("Size", this);
        QHBoxLayout *layout = new QHBoxLayout(group);

        layout->addWidget(makeTag("Large", QelTag::Primary, QelTag::Large));
        layout->addWidget(makeTag("Default", QelTag::Primary, QelTag::Default));
        layout->addWidget(makeTag("Small", QelTag::Primary, QelTag::Small));
        layout->addStretch();

        return group;
    }

    QGroupBox *createOptionsGroup()
    {
        QGroupBox *group = new QGroupBox("Options", this);
        QHBoxLayout *layout = new QHBoxLayout(group);

        QelTag *closable = makeTag("Closable", QelTag::Danger);
        closable->setClosable(true);
        layout->addWidget(closable);

        QelTag *hit = makeTag("Hit", QelTag::Success);
        hit->setHit(true);
        layout->addWidget(hit);

        QelTag *round = makeTag("Round", QelTag::Info);
        round->setRound(true);
        layout->addWidget(round);

        QelTag *custom = makeTag("Custom color", QelTag::Primary);
        custom->setColor("#7C3AED");
        layout->addWidget(custom);

        QelTag *noTransition = makeTag("No transition", QelTag::Warning);
        noTransition->setDisableTransitions(true);
        layout->addWidget(noTransition);

        layout->addStretch();
        return group;
    }

    QGroupBox *createEventsGroup()
    {
        QGroupBox *group = new QGroupBox("Events", this);
        QVBoxLayout *layout = new QVBoxLayout(group);

        QHBoxLayout *row = new QHBoxLayout();
        QelTag *tag = makeTag("Click or close me", QelTag::Primary);
        tag->setClosable(true);

        QLabel *result = new QLabel("Waiting for event...", group);
        result->setStyleSheet("color: #606266;");

        QObject::connect(tag, &QelTag::clicked, result, [result]() {
            result->setText("clicked()");
        });

        QObject::connect(
            tag,
            &QelTag::closeRequested,
            result,
            [tag, result]() {
                result->setText(
                    "closeRequested() — caller decides whether to remove Tag");
                tag->hide();
            });

        row->addWidget(tag);
        row->addWidget(result);
        row->addStretch();

        layout->addLayout(row);
        return group;
    }
};

#endif // QELTAGTESTER_H
