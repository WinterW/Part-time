#-------------------------------------------------
#
# Project created by QtCreator 2016-11-19T16:16:18
#
#-------------------------------------------------

QT       += core
QT       += gui
QT       += webenginewidgets
QT       += widgets
QT       += network

TARGET = auto_pay_demo
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    cwebhandler.cpp \
    cwebpage.cpp


INCLUDEPATH += $$PWD/../../../../usr/lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../../usr/lib/x86_64-linux-gnu

HEADERS += \
    cwebhandler.h \
    comm.h \
    cwebpage.h

unix:!macx: LIBS += -L$$PWD/../Qt5.7.0/5.7/gcc_64/lib/ -lQt5Gui

INCLUDEPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include
DEPENDPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include

unix:!macx: LIBS += -L$$PWD/../Qt5.7.0/5.7/gcc_64/lib/ -lQt5Core

INCLUDEPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include
DEPENDPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include

unix:!macx: LIBS += -L$$PWD/../Qt5.7.0/5.7/gcc_64/lib/ -lQt5WebEngineWidgets

INCLUDEPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include
DEPENDPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include

unix:!macx: LIBS += -L$$PWD/../Qt5.7.0/5.7/gcc_64/lib/ -lQt5Widgets

INCLUDEPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include
DEPENDPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include

unix:!macx: LIBS += -L$$PWD/../Qt5.7.0/5.7/gcc_64/lib/ -lQt5Network

INCLUDEPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include
DEPENDPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include

unix:!macx: LIBS += -L$$PWD/../Qt5.7.0/5.7/gcc_64/lib/ -lQt5Test

INCLUDEPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include
DEPENDPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include
