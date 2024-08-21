#ifndef QELBUTTONTESTER_H
#define QELBUTTONTESTER_H

#include "QelButton.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "../QelIcon/QelIcon.h"

using namespace qel;


class QelButtonTester : public QWidget {
    Q_OBJECT

public:
    explicit QelButtonTester(QWidget *parent = nullptr)
    {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

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
        iconButtons.append(new QelButton(QelButton::Default, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Search, 16), "", this));
        iconButtons.append(new QelButton(QelButton::Primary, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Edit, 16), "", this));
        iconButtons.append(new QelButton(QelButton::Success, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Check, 16), "", this));
        iconButtons.append(new QelButton(QelButton::Info, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Envelope, 16), "", this));
        iconButtons.append(new QelButton(QelButton::Warning, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Star, 16), "", this));
        iconButtons.append(new QelButton(QelButton::Danger, QelButton::Small, false, true, true, false, QelButton::Button, QelIcon(QelIcon::Trash, 16), "", this));
        addButtonRow(mainLayout, "Icon Buttons", iconButtons);

        setLayout(mainLayout);
    }

private:
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
};

#endif // QELBUTTONTESTER_H
