isEmpty(QEL_QELBUTTON_PRI_INCLUDED) {
    QEL_QELBUTTON_PRI_INCLUDED = 1

SOURCES += \
            $$PWD/QelButton.cpp
    
    HEADERS += \
            $$PWD/QelButton.h \
            $$PWD/../QelCommon/QelControlTypes.h
    
    include($$PWD/../QelTheme/QelTheme.pri)
    
    include($$PWD/../QelStyleHelper/QelStyleHelper.pri)
    include($$PWD/../QelAnimationHelper/QelAnimationHelper.pri)
    include($$PWD/../QelPopupManager/QelPopupManager.pri)
}
