#ifndef QELBUTTONTESTER_H
#define QELBUTTONTESTER_H

#include "QelButton.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "../QelAnimationHelper/QelAnimationHelper.h"
#include "../QelIcon/QelIcon.h"
#include "../QelPopupManager/QelPopupManager.h"

using namespace qel;

class QelButtonTester : public QWidget {
public:
    explicit QelButtonTester(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        QList<QelButton *> defaultButtons;
        defaultButtons.append(new QelButton(QelButton::Default, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Default", this));
        defaultButtons.append(new QelButton(QelButton::Primary, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Primary", this));
        defaultButtons.append(new QelButton(QelButton::Success, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Success", this));
        defaultButtons.append(new QelButton(QelButton::Info, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Info", this));
        defaultButtons.append(new QelButton(QelButton::Warning, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Warning", this));
        defaultButtons.append(new QelButton(QelButton::Danger, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Danger", this));
        addButtonRow(mainLayout, "Default Buttons", defaultButtons);

        QList<QelButton *> plainButtons;
        plainButtons.append(new QelButton(QelButton::Default, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Plain", this));
        plainButtons.append(new QelButton(QelButton::Primary, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Primary", this));
        plainButtons.append(new QelButton(QelButton::Success, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Success", this));
        plainButtons.append(new QelButton(QelButton::Info, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Info", this));
        plainButtons.append(new QelButton(QelButton::Warning, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Warning", this));
        plainButtons.append(new QelButton(QelButton::Danger, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Danger", this));
        addButtonRow(mainLayout, "Plain Buttons", plainButtons);

        QList<QelButton *> roundButtons;
        roundButtons.append(new QelButton(QelButton::Primary, QelButton::Medium, false, true, false, false, QelButton::Button, QIcon(), "Primary", this));
        roundButtons.append(new QelButton(QelButton::Success, QelButton::Medium, false, true, false, false, QelButton::Button, QIcon(), "Success", this));
        roundButtons.append(new QelButton(QelButton::Info, QelButton::Medium, false, true, false, false, QelButton::Button, QIcon(), "Info", this));
        roundButtons.append(new QelButton(QelButton::Warning, QelButton::Medium, false, true, false, false, QelButton::Button, QIcon(), "Warning", this));
        roundButtons.append(new QelButton(QelButton::Danger, QelButton::Medium, false, true, false, false, QelButton::Button, QIcon(), "Danger", this));
        addButtonRow(mainLayout, "Round Buttons", roundButtons);

        QList<QelButton *> iconButtons;
        iconButtons.append(new QelButton(QelButton::Default, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Search, 16, Qt::gray), "", this));
        iconButtons.append(new QelButton(QelButton::Primary, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Edit, 16, Qt::white), "", this));
        iconButtons.append(new QelButton(QelButton::Success, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Check, 16, Qt::white), "", this));
        iconButtons.append(new QelButton(QelButton::Info, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Envelope, 16, Qt::white), "", this));
        iconButtons.append(new QelButton(QelButton::Warning, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Star, 16, Qt::white), "", this));
        iconButtons.append(new QelButton(QelButton::Danger, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Trash, 16, Qt::white), "", this));
        addButtonRow(mainLayout, "Icon Buttons", iconButtons);

        QList<QelButton *> disabledButtons;
        disabledButtons.append(new QelButton(QelButton::Default, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Default", this));
        disabledButtons.append(new QelButton(QelButton::Primary, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Primary", this));
        disabledButtons.append(new QelButton(QelButton::Success, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Success", this));
        disabledButtons.append(new QelButton(QelButton::Info, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Info", this));
        disabledButtons.append(new QelButton(QelButton::Warning, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Warning", this));
        disabledButtons.append(new QelButton(QelButton::Danger, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Danger", this));
        for (QelButton *button : disabledButtons) {
            button->setDisabled(true);
        }
        addButtonRow(mainLayout, "Disabled Buttons", disabledButtons);

        QList<QelButton *> disabledPlainButtons;
        disabledPlainButtons.append(new QelButton(QelButton::Default, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Default", this));
        disabledPlainButtons.append(new QelButton(QelButton::Primary, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Primary", this));
        disabledPlainButtons.append(new QelButton(QelButton::Success, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Success", this));
        disabledPlainButtons.append(new QelButton(QelButton::Info, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Info", this));
        disabledPlainButtons.append(new QelButton(QelButton::Warning, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Warning", this));
        disabledPlainButtons.append(new QelButton(QelButton::Danger, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Danger", this));
        for (QelButton *button : disabledPlainButtons) {
            button->setDisabled(true);
        }
        addButtonRow(mainLayout, "Disabled Plain Buttons", disabledPlainButtons);

        QList<QelButton *> textButtons;
        textButtons.append(new QelButton(QelButton::Default, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Default Text", this));
        textButtons.append(new QelButton(QelButton::Primary, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Primary Text", this));
        textButtons.append(new QelButton(QelButton::Success, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Success Text", this));
        for (QelButton *button : textButtons) {
            button->setTextMode(true);
            button->setBg(true);
        }
        addButtonRow(mainLayout, "Text Buttons", textButtons);

        QList<QelButton *> linkButtons;
        linkButtons.append(new QelButton(QelButton::Default, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Default Link", this));
        linkButtons.append(new QelButton(QelButton::Primary, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Primary Link", this));
        linkButtons.append(new QelButton(QelButton::Danger, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Danger Link", this));
        for (QelButton *button : linkButtons) {
            button->setLinkMode(true);
        }
        addButtonRow(mainLayout, "Link Buttons", linkButtons);

        QList<QelButton *> customColorButtons;
        QelButton *customTeal = new QelButton(QelButton::Primary, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Custom #13c2c2", this);
        customTeal->setColor("#13c2c2");
        QelButton *customPurple = new QelButton(QelButton::Primary, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Custom #722ed1", this);
        customPurple->setColor("#722ed1");
        customColorButtons.append(customTeal);
        customColorButtons.append(customPurple);
        addButtonRow(mainLayout, "Custom Color Buttons", customColorButtons);

        QList<QelButton *> sizeButtons;
        sizeButtons.append(new QelButton(QelButton::Primary, QelButton::Large, false, false, false, false, QelButton::Button, QIcon(), "Large", this));
        sizeButtons.append(new QelButton(QelButton::Primary, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Medium", this));
        sizeButtons.append(new QelButton(QelButton::Primary, QelButton::Small, false, false, false, false, QelButton::Button, QIcon(), "Small", this));
        sizeButtons.append(new QelButton(QelButton::Primary, QelButton::Mini, false, false, false, false, QelButton::Button, QIcon(), "Mini", this));
        addButtonRow(mainLayout, "Button Sizes", sizeButtons);

        addElementPlusLinkTextShowcase(mainLayout);
        addPopupAndAnimationDemo(mainLayout);
        setLayout(mainLayout);
    }

private:
    QWidget *animationTarget_ = nullptr;

    void addButtonRow(QVBoxLayout *layout, const QString &title, const QList<QelButton *> &buttons)
    {
        QHBoxLayout *rowLayout = new QHBoxLayout();

        QLabel *label = new QLabel(title);
        rowLayout->addWidget(label);

        for (QelButton *button : buttons) {
            rowLayout->addWidget(button);
        }

        layout->addLayout(rowLayout);
    }

    void addElementPlusLinkTextShowcase(QVBoxLayout *layout)
    {
        QLabel *linkTitle = new QLabel("Link Button", this);
        linkTitle->setStyleSheet("font-size: 28px; font-weight: 700; color: #303133; margin-top: 8px;");
        layout->addWidget(linkTitle);

        QFrame *linkCard = createElementCard();
        QVBoxLayout *linkLayout = new QVBoxLayout(linkCard);
        linkLayout->setSpacing(10);
        linkLayout->addWidget(createElementSectionLabel("Basic link button"));

        QList<QelButton *> basicLinks = makeElementSemanticButtons(this);
        for (QelButton *button : basicLinks) {
            button->setLinkMode(true);
        }
        linkLayout->addLayout(makeElementRow(basicLinks));

        linkLayout->addWidget(createElementSectionLabel("Disabled link button"));
        QList<QelButton *> disabledLinks = makeElementSemanticButtons(this);
        for (QelButton *button : disabledLinks) {
            button->setLinkMode(true);
            button->setDisabled(true);
        }
        linkLayout->addLayout(makeElementRow(disabledLinks));
        layout->addWidget(linkCard);

        QLabel *textTitle = new QLabel("Text Button", this);
        textTitle->setStyleSheet("font-size: 28px; font-weight: 700; color: #303133; margin-top: 12px;");
        layout->addWidget(textTitle);

        QLabel *textDesc = new QLabel("Buttons without border and background.", this);
        textDesc->setStyleSheet("font-size: 18px; color: #606266;");
        layout->addWidget(textDesc);

        QFrame *textCard = createElementCard();
        QVBoxLayout *textLayout = new QVBoxLayout(textCard);
        textLayout->setSpacing(10);

        textLayout->addWidget(createElementSectionLabel("Basic text button"));
        QList<QelButton *> basicTexts = makeElementSemanticButtons(this);
        for (QelButton *button : basicTexts) {
            button->setTextMode(true);
        }
        textLayout->addLayout(makeElementRow(basicTexts));

        textLayout->addWidget(createElementSectionLabel("Background color always on"));
        QList<QelButton *> bgTexts = makeElementSemanticButtons(this);
        for (QelButton *button : bgTexts) {
            button->setTextMode(true);
            button->setBg(true);
        }
        textLayout->addLayout(makeElementRow(bgTexts));

        textLayout->addWidget(createElementSectionLabel("Disabled text button"));
        QList<QelButton *> disabledTexts = makeElementSemanticButtons(this);
        for (QelButton *button : disabledTexts) {
            button->setTextMode(true);
            button->setDisabled(true);
        }
        textLayout->addLayout(makeElementRow(disabledTexts));

        layout->addWidget(textCard);
    }

    QFrame *createElementCard()
    {
        QFrame *card = new QFrame(this);
        card->setStyleSheet("QFrame { background: #ffffff; border: 1px solid #dcdfe6; border-radius: 4px; }");
        return card;
    }

    QLabel *createElementSectionLabel(const QString &text)
    {
        QLabel *label = new QLabel(text, this);
        label->setStyleSheet("font-size: 16px; color: #303133; margin: 4px 0;");
        return label;
    }

    QList<QelButton *> makeElementSemanticButtons(QWidget *parent)
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

    QHBoxLayout *makeElementRow(const QList<QelButton *> &buttons)
    {
        QHBoxLayout *row = new QHBoxLayout();
        row->setSpacing(12);
        for (QelButton *button : buttons) {
            row->addWidget(button);
        }
        row->addStretch();
        return row;
    }

    void addPopupAndAnimationDemo(QVBoxLayout *layout)
    {
        QLabel *title = new QLabel("Popup && Animation Demo");
        layout->addWidget(title);

        QHBoxLayout *demoRow = new QHBoxLayout();
        QelButton *showPopupButton = new QelButton(QelButton::Primary, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Show Popup", this);
        QelButton *fadeButton = new QelButton(QelButton::Success, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Fade In/Out", this);
        QelButton *pressEffectButton = new QelButton(QelButton::Warning, QelButton::Medium, false, true, false, false, QelButton::Button, QIcon(), "Press Feedback", this);

        animationTarget_ = new QLabel("Animation Target", this);
        animationTarget_->setMinimumWidth(140);
        animationTarget_->setStyleSheet("QLabel{background:#f5f7fa;border:1px solid #dcdfe6;padding:6px;border-radius:4px;}");

        demoRow->addWidget(showPopupButton);
        demoRow->addWidget(fadeButton);
        demoRow->addWidget(pressEffectButton);
        demoRow->addWidget(animationTarget_);
        demoRow->addStretch();
        layout->addLayout(demoRow);

        connect(showPopupButton, &QelButton::clicked, this, [this, showPopupButton]() {
            QFrame *popup = new QFrame(nullptr, Qt::ToolTip);
            popup->setAttribute(Qt::WA_DeleteOnClose, true);
            popup->setStyleSheet("QFrame{background:#ffffff;border:1px solid #dcdfe6;border-radius:4px;} QLabel{padding:6px;color:#606266;}");

            QVBoxLayout *popupLayout = new QVBoxLayout(popup);
            popupLayout->setContentsMargins(8, 8, 8, 8);
            popupLayout->addWidget(new QLabel("QelPopupManager demo", popup));
            popupLayout->addWidget(new QLabel("- auto placement clamp", popup));
            popupLayout->addWidget(new QLabel("- zIndex allocate", popup));

            popup->resize(200, 90);

            const QPoint pos = QelPopupManager::computePopupPosition(showPopupButton, popup->size(), PopupPlacement::Bottom);
            popup->move(pos);
            popup->raise();
            popup->setWindowTitle(QString::number(QelPopupManager::acquireZIndex(PopupType::Popover)));
            QelPopupManager::registerPopup(popup, {PopupType::Popover, true, true, false});
            QelPopupManager::handleScreenBoundary(popup);

            popup->show();
            QelAnimationHelper::fadeIn(popup, 180);
            QTimer::singleShot(1600, popup, [popup]() {
                QelAnimationHelper::fadeOut(popup, 160);
            });
        });

        connect(fadeButton, &QelButton::clicked, this, [this]() {
            if (animationTarget_ == nullptr) {
                return;
            }

            if (animationTarget_->isVisible()) {
                QelAnimationHelper::fadeOut(animationTarget_, 140);
            } else {
                QelAnimationHelper::fadeIn(animationTarget_, 160);
            }
        });

        connect(pressEffectButton, &QelButton::clicked, this, [pressEffectButton]() {
            QelAnimationHelper::pressFeedback(pressEffectButton, 110);
        });
    }
};

#endif // QELBUTTONTESTER_H
