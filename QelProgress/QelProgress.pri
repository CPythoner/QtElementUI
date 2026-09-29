isEmpty(QEL_PROGRESS_PRI_INCLUDED) {
    QEL_PROGRESS_PRI_INCLUDED = 1

    SOURCES += \
        $$PWD/QelProgress.cpp

    HEADERS += \
        $$PWD/QelProgress.h

    include($$PWD/../QelTheme/QelTheme.pri)
    include($$PWD/../QelIcon/QelIcon.pri)
}
