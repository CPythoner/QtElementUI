#ifndef QELBUTTONTESTER_H
#define QELBUTTONTESTER_H

#include "QelButton.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
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

    void addPopupAndAnimationDemo(QVBoxLayout *layout)
    {
        QLabel *title = new QLabel("Popup && Animation Demo");
        layout->addWidget(title);

        QHBoxLayout *demoRow = new QHBoxLayout();
        QPushButton *showPopupButton = new QPushButton("Show Popup", this);
        QPushButton *fadeButton = new QPushButton("Fade In/Out", this);
        QPushButton *pressEffectButton = new QPushButton("Press Feedback", this);

        animationTarget_ = new QLabel("Animation Target", this);
        animationTarget_->setMinimumWidth(140);
        animationTarget_->setStyleSheet("QLabel{background:#f5f7fa;border:1px solid #dcdfe6;padding:6px;border-radius:4px;}");

        demoRow->addWidget(showPopupButton);
        demoRow->addWidget(fadeButton);
        demoRow->addWidget(pressEffectButton);
        demoRow->addWidget(animationTarget_);
        demoRow->addStretch();
        layout->addLayout(demoRow);

        connect(showPopupButton, &QPushButton::clicked, this, [this, showPopupButton]() {
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

        connect(fadeButton, &QPushButton::clicked, this, [this]() {
            if (animationTarget_ == nullptr) {
                return;
            }

            if (animationTarget_->isVisible()) {
                QelAnimationHelper::fadeOut(animationTarget_, 140);
            } else {
                QelAnimationHelper::fadeIn(animationTarget_, 160);
            }
        });

        connect(pressEffectButton, &QPushButton::clicked, this, [pressEffectButton]() {
            QelAnimationHelper::pressFeedback(pressEffectButton, 110);
        });
    }
};

#endif // QELBUTTONTESTER_H
