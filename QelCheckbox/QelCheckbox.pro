QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QelCheckbox
TEMPLATE = app

SOURCES += \
    main.cpp \
    QelCheckbox.cpp

HEADERS += \
    QelCheckbox.h \
    QelCheckboxTester.h

DISTFILES += \
    QelCheckbox.pri
