QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_lifelikecolorruletest.cpp \
    ../../GameOfLife/life_like_color_rule.cpp

HEADERS += \
    ../../GameOfLife/life_like_color_rule.h
