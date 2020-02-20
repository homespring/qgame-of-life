QT       += core gui widgets

TARGET = GameOfLife
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        cell.cpp \
        life_like_rule.cpp \
        main.cpp \
        game_window.cpp

HEADERS += \
        cell.h \
        game_window.h \
        life_like_rule.h \
        version.h

FORMS += \
        game_window.ui

target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
