QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QelSelect
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
    main.cpp \
    QelSelect.cpp

HEADERS += \
    QelSelect.h \
    QelSelectTester.h

DISTFILES += \
    QelSelect.pri

include($$PWD/../QelIcon/QelIcon.pri)
