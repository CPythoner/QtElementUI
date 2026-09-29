isEmpty(QEL_BADGE_PRI_INCLUDED) {
    QEL_BADGE_PRI_INCLUDED = 1

    SOURCES += \
        $$PWD/QelBadge.cpp

    HEADERS += \
        $$PWD/QelBadge.h

    include($$PWD/../QelTheme/QelTheme.pri)
}
