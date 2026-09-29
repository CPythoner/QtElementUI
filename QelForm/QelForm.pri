isEmpty(QEL_QELFORM_PRI_INCLUDED) {
    QEL_QELFORM_PRI_INCLUDED = 1

SOURCES += \
        $$PWD/QelForm.cpp
    
    HEADERS += \
        $$PWD/QelForm.h \
        $$PWD/QelFormRule.h
    
    include($$PWD/../QelTheme/QelTheme.pri)
}
