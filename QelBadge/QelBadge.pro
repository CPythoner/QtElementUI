QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QelBadge
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++17

SOURCES += \
    main.cpp

HEADERS += \
    QelBadgeTester.h

include($$PWD/QelBadge.pri)
include($PWD/../QelButton/QelButton.pri)
include($PWD/../QelIcon/QelIcon.pri)
include($$PWD/../QelTag/QelTag.pri)

DISTFILES += \
    QelBadge.pri
