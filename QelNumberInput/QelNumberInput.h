#ifndef QELNUMBERINPUT_H
#define QELNUMBERINPUT_H

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

namespace qel {

class QelNumberInput : public QWidget {
    Q_OBJECT

public:
    enum Size {
        Small,
        Default,
        Large
    };

    explicit QelNumberInput(QWidget *parent = nullptr,
                            int minValue = -std::numeric_limits<int>::max(),
                            int maxValue = std::numeric_limits<int>::max(),
                            double initialValue = 0,
                            double step = 1,
                            bool readonly = false,
                            bool disabled = false,
                            bool controls = true,
                            const QString &placeholder = "");

    double value() const;
    void setValue(double value);
    void setMinValue(int minValue);
    void setMaxValue(int maxValue);
    void setStep(double step);
    void setReadonly(bool readonly);
    void setDisabled(bool disabled);
    void setPlaceholder(const QString &placeholder);
    void setSize(Size size);
    void setPrecision(int precision);

protected:
    void focusInEvent(QFocusEvent *event) override;    // 声明 focusInEvent
    void focusOutEvent(QFocusEvent *event) override;   // 声明 focusOutEvent
    void paintEvent(QPaintEvent *event) override;      // 声明 paintEvent
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void valueChanged(double newValue);
    void decreaseIconClicked();
    void increaseIconClicked();

private slots:
    void onIncrease();
    void onDecrease();
    void onFocusIn();
    void onFocusOut();

private:
    QPushButton *decreaseButton;
    QPushButton *increaseButton;
    QLineEdit *valueDisplay;
    QWidget *container;

    int minValue;
    int maxValue;
    double step;
    double currentValue;
    bool readonly;
    bool disabled;
    bool controls;
    Size size;
    int precision;

    void updateDisplay();
    void updateControlsState();
};

}

#endif // QELNUMBERINPUT_H
