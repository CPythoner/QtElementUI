isEmpty(QEL_QELSELECT_PRI_INCLUDED) {
    QEL_QELSELECT_PRI_INCLUDED = 1

SOURCES += \
        $$PWD/QelSelect.cpp
    
    HEADERS += \
        $$PWD/QelSelect.h
    
    include($$PWD/../QelIcon/QelIcon.pri)
    include($$PWD/../QelStyleHelper/QelStyleHelper.pri)
}
