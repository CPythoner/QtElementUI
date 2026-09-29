QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QelTag
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++17

SOURCES += \
    main.cpp

HEADERS += \
    QelTagTester.h

include($$PWD/QelTag.pri)

DISTFILES += \
    QelTag.pri
