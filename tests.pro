QT += testlib
QT += core
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tests/tst_statehandlers.cpp \
    util/statehandlers.cpp \
    src/player.cpp \
    src/state.cpp \
    util/moves.cpp \
    util/lineid.cpp

INCLUDEPATH += .
DEPENDPATH += .

