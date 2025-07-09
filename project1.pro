QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/game.cpp \
    src/player.cpp \
    src/pokemon.cpp \
    src/state.cpp \
    util/lineid.cpp \
    util/moves.cpp \
    util/statehandlers.cpp

HEADERS += \
    headers/game.h \
    headers/player.h \
    headers/pokemon.h \
    headers/state.h \
    mainwindow.h \
    util/lineid.h \
    util/statehandlers.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

DISTFILES += \
    .gitignore \
    README.md \
