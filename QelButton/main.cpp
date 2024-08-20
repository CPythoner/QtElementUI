#include "qelbutton.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qel::QelButton w(NULL,
                     "Primary",
                     qel::ButtonSize::Medium,
                     qel::ButtonType::Primary,
                     true,
                     true,
                     false);
    w.setText("主要按钮");
    w.show();

    return a.exec();
}
