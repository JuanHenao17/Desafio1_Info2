TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
QT += core gui
INCLUDEPATH += include

SOURCES += \
        main.cpp \
        src/operacionesBit.cpp \
        src/procesamiento.cpp \
        src/verificaciones.cpp

HEADERS += \
    include/operacionesBit.h \
    include/procesamiento.h \
    include/verificaciones.h
