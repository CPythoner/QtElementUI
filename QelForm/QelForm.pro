QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QelForm
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
    main.cpp

HEADERS += \
    QelFormTester.h

include($$PWD/QelForm.pri)
include($$PWD/../QelButton/QelButton.pri)
include($$PWD/../QelInput/QelInput.pri)
include($$PWD/../QelSelect/QelSelect.pri)

DISTFILES += \
    QelForm.pri
