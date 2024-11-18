HEADERS += \
        $$PWD/QelIcon.h

RESOURCES += \
    $$PWD/resources.qrc

# 添加字体文件到资源系统
RESOURCES += \
    $$PWD/fonts.qrc

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# 确保目标目录存在
mkpath($$OUT_PWD/fonts)

# 复制字体文件
win32 {
    QMAKE_POST_LINK += $$QMAKE_COPY $$shell_quote($$PWD/fonts/fontawesome-4.7.0.ttf) $$shell_quote($$OUT_PWD/fonts) $$escape_expand(\\n\\t)
} else {
    QMAKE_POST_LINK += $$QMAKE_COPY $$shell_quote($$PWD/fonts/fontawesome-4.7.0.ttf) $$shell_quote($$OUT_PWD/fonts) $$escape_expand(\n\t)
}
