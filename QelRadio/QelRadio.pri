isEmpty(QEL_QELRADIO_PRI_INCLUDED) {
    QEL_QELRADIO_PRI_INCLUDED = 1

SOURCES += \
        $$PWD/QelRadio.cpp
    
    HEADERS += \
        $$PWD/QelRadio.h
    
    include($$PWD/../QelStyleHelper/QelStyleHelper.pri)
}
