QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_celltest.cpp \
    ../../GameOfLife/life_like_cell.cpp \
    ../../GameOfLife/life_like_rule.cpp

HEADERS += \
    ../../GameOfLife/life_like_cell.h \
    ../../GameOfLife/life_like_rule.h
