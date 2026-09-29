isEmpty(QEL_QELINPUT_PRI_INCLUDED) {
    QEL_QELINPUT_PRI_INCLUDED = 1

SOURCES += \
        $$PWD/QelInput.cpp
    
    HEADERS += \
        $$PWD/QelInput.h
    
    include($$PWD/../QelStyleHelper/QelStyleHelper.pri)
}
