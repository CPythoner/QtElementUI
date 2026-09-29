isEmpty(QEL_QELSWITCH_PRI_INCLUDED) {
    QEL_QELSWITCH_PRI_INCLUDED = 1

SOURCES += \
        $$PWD/QelSwitch.cpp
    
    HEADERS += \
        $$PWD/QelSwitch.h
    
    include($$PWD/../QelStyleHelper/QelStyleHelper.pri)
}
