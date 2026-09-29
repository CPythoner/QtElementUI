isEmpty(QEL_STYLE_HELPER_PRI_INCLUDED) {
    QEL_STYLE_HELPER_PRI_INCLUDED = 1

    SOURCES += \
        $$PWD/QelStyleHelper.cpp

    HEADERS += \
        $$PWD/QelStyleHelper.h

    include($$PWD/../QelTheme/QelTheme.pri)
}
