isEmpty(QEL_TAG_PRI_INCLUDED) {
    QEL_TAG_PRI_INCLUDED = 1

    SOURCES += \
        $$PWD/QelTag.cpp

    HEADERS += \
        $$PWD/QelTag.h

    include($$PWD/../QelTheme/QelTheme.pri)
    include($$PWD/../QelAnimationHelper/QelAnimationHelper.pri)
}
