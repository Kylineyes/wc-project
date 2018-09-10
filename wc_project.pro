TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    src/getopt.c \
    wstringtool.cpp \
    src/work.cpp

HEADERS += \
    src/getopt.h \
    wstringtool.h \
    src/work.h
