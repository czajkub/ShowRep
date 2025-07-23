QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += charts

CONFIG += c++23

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
    src/webreplay.cpp \
    util/lineid.cpp \
    util/moves.cpp \
    util/statehandlers.cpp

HEADERS += \
    include/game.h \
    include/player.h \
    include/pokemon.h \
    include/state.h \
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

SUBDIRS += \
    tests.pro



win32:CONFIG(release, debug|release): LIBS += -L$$_PRO_FILE_PWD_/curl/lib -lcurl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$_PRO_FILE_PWD_/curl/lib -lcurl

INCLUDEPATH += $$_PRO_FILE_PWD_/curl/include
DEPENDPATH += $$_PRO_FILE_PWD_/curl/include
