TEMPLATE = app
CONFIG += console
CONFIG += c11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += csc/csc_dlist.h
HEADERS += csc/csc_htable.h
HEADERS += csc/csc_debug.h
HEADERS += csc/csc_basic.h
HEADERS += csc/csc_str.h
HEADERS += csc/csc_strf.h
SOURCES += pactest.c
INCLUDEPATH += csc
