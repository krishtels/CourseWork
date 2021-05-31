QT       += core gui
QT += multimedia multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attack.cpp \
    button.cpp \
    drivehorizontalplatform.cpp \
    fallingplatform.cpp \
    gamecontrol.cpp \
    gamehelper.cpp \
    ghost.cpp \
    main.cpp \
    mainwindow.cpp \
    movingplatform.cpp \
    multiplier.cpp \
    platform.cpp \
    playdoodle.cpp \
    simpleplatform.cpp \
    springboots.cpp \
    stopplatform.cpp \
    threat.cpp

HEADERS += \
    attack.h \
    button.h \
    definition.h \
    drivehorizontalplatform.h \
    fallingplatform.h \
    gamecontrol.h \
    gamehelper.h \
    ghost.h \
    mainwindow.h \
    movingplatform.h \
    multiplier.h \
    platform.h \
    playdoodle.h \
    simpleplatform.h \
    springboots.h \
    stopplatform.h \
    threat.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
