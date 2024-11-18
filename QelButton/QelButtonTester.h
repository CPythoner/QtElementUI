#ifndef QELBUTTONTESTER_H
#define QELBUTTONTESTER_H

#include "QelButton.h"
#include "QelButtonGroup.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "../QelIcon/QelIcon.h"

using namespace qel;


class QelButtonTester : public QWidget {
    Q_OBJECT
public:
    explicit QelButtonTester(QWidget *parent = nullptr) : QWidget(parent), mainLayout(new QVBoxLayout(this))
    {
        // Default buttons
        QList<QelButton *> defaultButtons;
        defaultButtons.append(new QelButton(QelButton::Default, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Default", this));
        defaultButtons.append(new QelButton(QelButton::Primary, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Primary", this));
        defaultButtons.append(new QelButton(QelButton::Success, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Success", this));
        defaultButtons.append(new QelButton(QelButton::Info, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Info", this));
        defaultButtons.append(new QelButton(QelButton::Warning, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Warning", this));
        defaultButtons.append(new QelButton(QelButton::Danger, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Danger", this));
        addButtonRow(mainLayout, "Default Buttons", defaultButtons);

        // Plain buttons
        QList<QelButton *> plainButtons;
        plainButtons.append(new QelButton(QelButton::Default, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Plain", this));
        plainButtons.append(new QelButton(QelButton::Primary, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Primary", this));
        plainButtons.append(new QelButton(QelButton::Success, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Success", this));
        plainButtons.append(new QelButton(QelButton::Info, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Info", this));
        plainButtons.append(new QelButton(QelButton::Warning, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Warning", this));
        plainButtons.append(new QelButton(QelButton::Danger, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Danger", this));
        addButtonRow(mainLayout, "Plain Buttons", plainButtons);

        // Round buttons
        QList<QelButton *> roundButtons;
        roundButtons.append(new QelButton(QelButton::Primary, QelButton::Medium, false, true, false, false, QelButton::Button, QIcon(), "Primary", this));
        roundButtons.append(new QelButton(QelButton::Success, QelButton::Medium, false, true, false, false, QelButton::Button, QIcon(), "Success", this));
        roundButtons.append(new QelButton(QelButton::Info, QelButton::Medium, false, true, false, false, QelButton::Button, QIcon(), "Info", this));
        roundButtons.append(new QelButton(QelButton::Warning, QelButton::Medium, false, true, false, false, QelButton::Button, QIcon(), "Warning", this));
        roundButtons.append(new QelButton(QelButton::Danger, QelButton::Medium, false, true, false, false, QelButton::Button, QIcon(), "Danger", this));
        addButtonRow(mainLayout, "Round Buttons", roundButtons);

        // Icon buttons
        QList<QelButton *> iconButtons;
        iconButtons.append(new QelButton(QelButton::Default, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Search, 16, Qt::gray), "", this));
        iconButtons.append(new QelButton(QelButton::Primary, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Edit, 16, Qt::white), "", this));
        iconButtons.append(new QelButton(QelButton::Success, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Check, 16, Qt::white), "", this));
        iconButtons.append(new QelButton(QelButton::Info, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Envelope, 16, Qt::white), "", this));
        iconButtons.append(new QelButton(QelButton::Warning, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Star, 16, Qt::white), "", this));
        iconButtons.append(new QelButton(QelButton::Danger, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Trash, 16, Qt::white), "", this));
        addButtonRow(mainLayout, "Icon Buttons", iconButtons);

        // Disabled buttons
        QList<QelButton *> disabledButtons;
        disabledButtons.append(new QelButton(QelButton::Default, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Default", this));
        disabledButtons.append(new QelButton(QelButton::Primary, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Primary", this));
        disabledButtons.append(new QelButton(QelButton::Success, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Success", this));
        disabledButtons.append(new QelButton(QelButton::Info, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Info", this));
        disabledButtons.append(new QelButton(QelButton::Warning, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Warning", this));
        disabledButtons.append(new QelButton(QelButton::Danger, QelButton::Medium, false, false, false, false, QelButton::Button, QIcon(), "Danger", this));

        // 设置所有按钮为禁用状态
        for (QelButton *button : disabledButtons) {
            button->setDisabled(true);
        }
        addButtonRow(mainLayout, "Disabled Buttons", disabledButtons);

        // Disabled Plain buttons
        QList<QelButton *> disabledPlainButtons;
        disabledPlainButtons.append(new QelButton(QelButton::Default, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Default", this));
        disabledPlainButtons.append(new QelButton(QelButton::Primary, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Primary", this));
        disabledPlainButtons.append(new QelButton(QelButton::Success, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Success", this));
        disabledPlainButtons.append(new QelButton(QelButton::Info, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Info", this));
        disabledPlainButtons.append(new QelButton(QelButton::Warning, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Warning", this));
        disabledPlainButtons.append(new QelButton(QelButton::Danger, QelButton::Medium, true, false, false, false, QelButton::Button, QIcon(), "Danger", this));

                // 设置所有按钮为禁用状态
        for (QelButton *button : disabledPlainButtons) {
            button->setDisabled(true);
        }
        addButtonRow(mainLayout, "Disabled Plain Buttons", disabledPlainButtons);

        setupButtonGroups();
    }

private:
    QVBoxLayout *mainLayout;

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

    void setupButtonGroups()
    {
        QLabel* groupLabel = new QLabel("Button Groups", this);
        mainLayout->addWidget(groupLabel);

        // 创建基础按钮组
        QelButtonGroup* basicGroup = new QelButtonGroup(this);
        QelButton* prevBtn = new QelButton(QelButton::Primary, QelButton::Medium, false, false, false, false,
                                         QelButton::Button, QelIcon(QelIcon::ArrowLeft, 16, Qt::white),
                                         "Previous Page", this);
        QelButton* nextBtn = new QelButton(QelButton::Primary, QelButton::Medium, false, false, false, false,
                                         QelButton::Button, QelIcon(QelIcon::ArrowRight, 16, Qt::white),
                                         "Next Page", this);
        basicGroup->addButton(prevBtn);
        basicGroup->addButton(nextBtn);
        mainLayout->addWidget(basicGroup);

        // 创建图标按钮组
        QelButtonGroup* iconGroup = new QelButtonGroup(this);
        QList<QelIcon::Icon> icons = {QelIcon::Edit, QelIcon::Share, QelIcon::Trash};
        for (auto icon : icons) {
            QelButton* btn = new QelButton(QelButton::Primary, QelButton::Medium, false, false, false, false,
                                         QelButton::Button, QelIcon(icon, 16, Qt::white), "", this);
            iconGroup->addButton(btn);
        }
        mainLayout->addWidget(iconGroup);
    }
};

#endif // QELBUTTONTESTER_H
