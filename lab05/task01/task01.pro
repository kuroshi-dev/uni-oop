TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        instrument.cpp \
        leader.cpp \
        main.cpp \
        manager.cpp \
        musicband.cpp \
        musician.cpp \
        person.cpp

HEADERS += \
    instrument.h \
    leader.h \
    manager.h \
    musicband.h \
    musician.h \
    person.h
