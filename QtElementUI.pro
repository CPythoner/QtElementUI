TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    QelIcon \
    QelButton \
    QelNumberInput \
    QelShow

# 设置依赖关系
QelButton.depends = QelIcon
QelShow.depends = QelIcon QelButton QelNumberInput

# 添加构建配置
CONFIG += debug_and_release
CONFIG += c++11
