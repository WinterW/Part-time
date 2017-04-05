#-------------------------------------------------
#
# Project created by QtCreator 2016-11-22T16:30:38
#
#-------------------------------------------------

QT       += widgets network
CONFIG   -= console
#QT       -= gui

TARGET = auto_pay
TEMPLATE = lib

DEFINES += AUTO_PAY_LIBRARY
release:DEFINES += QT_NO_DEBUG_OUTPUT
SOURCES += auto_pay.cpp \
    ../auto_pay_demo_5.7/cwebpage.cpp \
    ../auto_pay_demo_5.7/cwebhandler.cpp \
    auto_pay_context.cpp \
    ../com_auto_pay/com_auto_pay_auto_pay_native.cpp

HEADERS += auto_pay.h\
        auto_pay_global.h \
    ../auto_pay_demo_5.7/cwebpage.h \
    ../auto_pay_demo_5.7/cwebhandler.h \
    ../auto_pay_demo_5.7/comm.h \
    auto_pay_context.h \
    ../com_auto_pay/com_auto_pay_auto_pay_native.h \
    ../com_auto_pay/jni.h \
    ../com_auto_pay/jni_md.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$PWD/../Qt5.7.0/5.7/gcc_64/lib/ -lQt5WebEngineWidgets

INCLUDEPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include
DEPENDPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include
