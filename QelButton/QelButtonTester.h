#ifndef QELBUTTONTESTER_H
#define QELBUTTONTESTER_H

#include "QelButton.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

using namespace qel;

class QelButtonTester : public QWidget {
public:
    explicit QelButtonTester(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(16);

        QLabel *linkTitle = new QLabel("Link Button", this);
        linkTitle->setStyleSheet("font-size: 28px; font-weight: 700; color: #303133;");
        mainLayout->addWidget(linkTitle);

        QFrame *linkCard = createCard();
        QVBoxLayout *linkLayout = new QVBoxLayout(linkCard);
        linkLayout->addWidget(makeSectionLabel("Basic link button"));

        QList<QelButton *> basicLinks = makeSemanticButtons(this);
        for (QelButton *button : basicLinks) {
            button->setLinkMode(true);
        }
        linkLayout->addLayout(makeButtonRow(basicLinks));

        linkLayout->addWidget(makeSectionLabel("Disabled link button"));
        QList<QelButton *> disabledLinks = makeSemanticButtons(this);
        for (QelButton *button : disabledLinks) {
            button->setLinkMode(true);
            button->setDisabled(true);
        }
        linkLayout->addLayout(makeButtonRow(disabledLinks));
        mainLayout->addWidget(linkCard);

        QLabel *textTitle = new QLabel("Text Button", this);
        textTitle->setStyleSheet("font-size: 28px; font-weight: 700; color: #303133;");
        mainLayout->addWidget(textTitle);

        QLabel *textDesc = new QLabel("Buttons without border and background.", this);
        textDesc->setStyleSheet("font-size: 18px; color: #606266;");
        mainLayout->addWidget(textDesc);

        QFrame *textCard = createCard();
        QVBoxLayout *textLayout = new QVBoxLayout(textCard);

        textLayout->addWidget(makeSectionLabel("Basic text button"));
        QList<QelButton *> basicTexts = makeSemanticButtons(this);
        for (QelButton *button : basicTexts) {
            button->setTextMode(true);
        }
        textLayout->addLayout(makeButtonRow(basicTexts));

        textLayout->addWidget(makeSectionLabel("Background color always on"));
        QList<QelButton *> bgTexts = makeSemanticButtons(this);
        for (QelButton *button : bgTexts) {
            button->setTextMode(true);
            button->setBg(true);
        }
        textLayout->addLayout(makeButtonRow(bgTexts));

        textLayout->addWidget(makeSectionLabel("Disabled text button"));
        QList<QelButton *> disabledTexts = makeSemanticButtons(this);
        for (QelButton *button : disabledTexts) {
            button->setTextMode(true);
            button->setDisabled(true);
        }
        textLayout->addLayout(makeButtonRow(disabledTexts));

        mainLayout->addWidget(textCard);
        mainLayout->addStretch();
        setLayout(mainLayout);
        setStyleSheet("QWidget { background: #f5f7fa; }");
    }

private:
    QFrame *createCard()
    {
        QFrame *card = new QFrame(this);
        card->setStyleSheet("QFrame { background: #ffffff; border: 1px solid #dcdfe6; border-radius: 4px; }");
        return card;
    }

    QLabel *makeSectionLabel(const QString &text)
    {
        QLabel *label = new QLabel(text, this);
        label->setStyleSheet("font-size: 16px; color: #303133; margin: 8px 0;");
        return label;
    }

    QList<QelButton *> makeSemanticButtons(QWidget *parent)
    {
        QList<QelButton *> buttons;
        buttons.append(new QelButton(QelButton::Default, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "plain", parent));
        buttons.append(new QelButton(QelButton::Primary, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "primary", parent));
        buttons.append(new QelButton(QelButton::Success, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "success", parent));
        buttons.append(new QelButton(QelButton::Info, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "info", parent));
        buttons.append(new QelButton(QelButton::Warning, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "warning", parent));
        buttons.append(new QelButton(QelButton::Danger, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "danger", parent));
        return buttons;
    }

    QHBoxLayout *makeButtonRow(const QList<QelButton *> &buttons)
    {
        QHBoxLayout *row = new QHBoxLayout();
        row->setSpacing(12);
        for (QelButton *button : buttons) {
            row->addWidget(button);
        }
        row->addStretch();
        return row;
    }
};

#endif // QELBUTTONTESTER_H
