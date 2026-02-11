QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QelRadio
TEMPLATE = app

SOURCES += \
    main.cpp \
    QelRadio.cpp

HEADERS += \
    QelRadio.h \
    QelRadioTester.h

DISTFILES += \
    QelRadio.pri
