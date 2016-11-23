#-------------------------------------------------
#
# Project created by QtCreator 2016-11-19T16:16:18
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = auto_pay_demo
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    cwebhandler.cpp \
    cwebpage.cpp \
    cnetworkaccessmanager.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/Trolltech/Qt-4.8.6/lib/release/ -lQtGui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/Trolltech/Qt-4.8.6/lib/debug/ -lQtGui
else:symbian: LIBS += -lQtGui
else:unix: LIBS += -L$$PWD/../../../../usr/local/Trolltech/Qt-4.8.6/lib/ -lQtGui

INCLUDEPATH += $$PWD/../../../../usr/local/Trolltech/Qt-4.8.6/include
DEPENDPATH += $$PWD/../../../../usr/local/Trolltech/Qt-4.8.6/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/Trolltech/Qt-4.8.6/lib/release/ -lQtCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/Trolltech/Qt-4.8.6/lib/debug/ -lQtCore
else:symbian: LIBS += -lQtCore
else:unix: LIBS += -L$$PWD/../../../../usr/local/Trolltech/Qt-4.8.6/lib/ -lQtCore

INCLUDEPATH += $$PWD/../../../../usr/local/Trolltech/Qt-4.8.6/include
DEPENDPATH += $$PWD/../../../../usr/local/Trolltech/Qt-4.8.6/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/release/ -lQtWebKit
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/debug/ -lQtWebKit
else:symbian: LIBS += -lQtWebKit
else:unix: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/ -lQtWebKit

INCLUDEPATH += $$PWD/../../../../usr/lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../../usr/lib/x86_64-linux-gnu

HEADERS += \
    cwebhandler.h \
    comm.h \
    cwebpage.h \
    cnetworkaccessmanager.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/Trolltech/Qt-4.8.6/lib/release/ -lQtNetwork
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/Trolltech/Qt-4.8.6/lib/debug/ -lQtNetwork
else:symbian: LIBS += -lQtNetwork
else:unix: LIBS += -L$$PWD/../../../../usr/local/Trolltech/Qt-4.8.6/lib/ -lQtNetwork

INCLUDEPATH += $$PWD/../../../../usr/local/Trolltech/Qt-4.8.6/include
DEPENDPATH += $$PWD/../../../../usr/local/Trolltech/Qt-4.8.6/include
