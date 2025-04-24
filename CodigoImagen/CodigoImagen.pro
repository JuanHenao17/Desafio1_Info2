TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
QT += core gui
INCLUDEPATH += include

SOURCES += \
        main.cpp \
        src/enmascaramiento.cpp \
        src/operacionesBit.cpp \
        src/procesamiento.cpp

HEADERS += \
    include/enmascaramiento.h \
    include/operacionesBit.h \
    include/procesamiento.h
