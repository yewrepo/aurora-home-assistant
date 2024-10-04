TEMPLATE = app
TARGET = runner
CONFIG += console c++11
QT -= gui
SOURCES += \
        main.cpp

target.path = /usr/libexec/ru.yewrepo.auroraassistant/
INSTALLS += target
