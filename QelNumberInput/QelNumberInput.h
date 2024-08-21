#ifndef QELNUMBERINPUT_H
#define QELNUMBERINPUT_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

namespace qel {

class QelNumberInput : public QWidget {
    Q_OBJECT

public:
    enum class Size { Small, Default, Large };
    enum class ControlsPosition { Default, Right };  // 添加 ControlsPosition 枚举

    explicit QelNumberInput(QWidget *parent = nullptr,
                            int minValue = 0,
                            int maxValue = 100,
                            double initialValue = 0,
                            double step = 1,
                            bool readonly = false,
                            bool disabled = false,
                            bool controls = true,
                            ControlsPosition controlsPosition = ControlsPosition::Default,  // 使用枚举类型
                            const QString &placeholder = "");

    void setSize(Size size);
    void setPrecision(int precision);
    void setControlsPosition(ControlsPosition position);  // 添加 setControlsPosition 函数

    double value() const;
    void setValue(double value);

    void setMinValue(int minValue);
    void setMaxValue(int maxValue);
    void setStep(double step);
    void setReadonly(bool readonly);
    void setDisabled(bool disabled);
    void setPlaceholder(const QString &placeholder);

signals:
    void valueChanged(double value);
    void increaseIconClicked();
    void decreaseIconClicked();

private:
    int minValue;
    int maxValue;
    double currentValue;
    double step;
    bool readonly;
    bool disabled;
    bool controls;
    Size size;
    int precision;
    ControlsPosition controlsPosition;  // 使用枚举类型

    QPushButton *decreaseButton;
    QPushButton *increaseButton;
    QLineEdit *valueDisplay;

    void onIncrease();
    void onDecrease();
    void updateDisplay();
    void updateControlsState();
};

}

#endif // QELNUMBERINPUT_H
