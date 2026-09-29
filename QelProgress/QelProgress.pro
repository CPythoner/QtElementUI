QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QelProgress
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++17

SOURCES += \
    main.cpp

HEADERS += \
    QelProgressTester.h

include($$PWD/QelProgress.pri)
include($$PWD/../QelButton/QelButton.pri)

DISTFILES += \
    QelProgress.pri
