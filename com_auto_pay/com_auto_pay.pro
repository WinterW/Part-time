#-------------------------------------------------
#
# Project created by QtCreator 2016-12-03T01:15:31
#
#-------------------------------------------------

QT       -= core gui

TARGET = com_auto_pay
TEMPLATE = lib

DEFINES += COM_AUTO_PAY_LIBRARY

SOURCES += \
    com_auto_pay_auto_pay_native.cpp

HEADERS +=\
    jni_md.h \
    jni.h \
    com_auto_pay_auto_pay_native.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$PWD/../auto_pay/ -lauto_pay

INCLUDEPATH += $$PWD/../auto_pay
DEPENDPATH += $$PWD/../auto_pay

unix:!macx: LIBS += -L$$PWD/../Qt5.7.0/5.7/gcc_64/lib/ -lQt5Core

INCLUDEPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include
DEPENDPATH += $$PWD/../Qt5.7.0/5.7/gcc_64/include
