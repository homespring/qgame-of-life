QT       += core gui widgets

TARGET = GameOfLife
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        life_like_biome.cpp \
        life_like_cell.cpp \
        life_like_color_rule.cpp \
        life_like_game.cpp \
        life_like_rule.cpp \
        main.cpp \
        game_window.cpp

HEADERS += \
        game_window.h \
        life_like_biome.h \
        life_like_cell.h \
        life_like_color_rule.h \
        life_like_game.h \
        life_like_rule.h \
        version.h

FORMS += \
        game_window.ui

target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
