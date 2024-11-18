QT       += core gui widgets

TEMPLATE = app
CONFIG += c++17

SOURCES += \
    QelSelect.cpp \
    main.cpp

HEADERS += \
    QelSelect.h \
    qelselecttester.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/../

RESOURCES += qelselect.qrc
