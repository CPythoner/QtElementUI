isEmpty(QEL_QELCHECKBOX_PRI_INCLUDED) {
    QEL_QELCHECKBOX_PRI_INCLUDED = 1

SOURCES += \
        $$PWD/QelCheckbox.cpp
    
    HEADERS += \
        $$PWD/QelCheckbox.h
    
    include($$PWD/../QelStyleHelper/QelStyleHelper.pri)
}
