#-------------------------------------------------
#
# Project created by QtCreator 2021-03-13T23:06:12
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = QelButton
TEMPLATE = app

CONFIG += c++11
CONFIG += debug_and_release

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    QelButton.cpp \
    QelButtonGroup.cpp

HEADERS += \
    QelButton.h \
    QelButtonGroup.h \
    QelButtonTester.h

# 包含 QelIcon
include($$PWD/../QelIcon/QelIcon.pri)

INCLUDEPATH += $$PWD/..
DEPENDPATH += $$PWD/..

# 设置输出目录
CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/../debug
    OBJECTS_DIR = debug
    MOC_DIR = debug
    RCC_DIR = debug
    UI_DIR = debug
} else {
    DESTDIR = $$OUT_PWD/../release
    OBJECTS_DIR = release
    MOC_DIR = release
    RCC_DIR = release
    UI_DIR = release
}

# 确保输出目录存在
mkpath($$DESTDIR)
