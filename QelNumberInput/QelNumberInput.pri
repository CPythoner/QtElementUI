isEmpty(QEL_QELNUMBERINPUT_PRI_INCLUDED) {
    QEL_QELNUMBERINPUT_PRI_INCLUDED = 1

SOURCES += \
        $$PWD/QelNumberInput.cpp
    
    HEADERS += \
        $$PWD/QelNumberInput.h
    
    include($$PWD/../QelStyleHelper/QelStyleHelper.pri)
}
