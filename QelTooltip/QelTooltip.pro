QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QelTooltip
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
    main.cpp

HEADERS += \
    QelTooltipTester.h

include($$PWD/QelTooltip.pri)
include($$PWD/../QelButton/QelButton.pri)

DISTFILES += \
    QelTooltip.pri
