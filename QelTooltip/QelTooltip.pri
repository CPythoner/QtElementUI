isEmpty(QEL_QELTOOLTIP_PRI_INCLUDED) {
    QEL_QELTOOLTIP_PRI_INCLUDED = 1

SOURCES += \
        $$PWD/QelTooltip.cpp
    
    HEADERS += \
        $$PWD/QelTooltip.h
    
    include($$PWD/../QelTheme/QelTheme.pri)
    include($$PWD/../QelAnimationHelper/QelAnimationHelper.pri)
    include($$PWD/../QelPopupManager/QelPopupManager.pri)
}
