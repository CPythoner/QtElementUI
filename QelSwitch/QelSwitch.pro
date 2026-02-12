QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QelSwitch
TEMPLATE = app

SOURCES += \
    main.cpp \
    QelSwitch.cpp

HEADERS += \
    QelSwitch.h \
    QelSwitchTester.h

DISTFILES += \
    QelSwitch.pri
