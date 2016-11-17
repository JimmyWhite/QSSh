#-------------------------------------------------
#
# Project created by QtCreator 2016-10-12T13:28:52
#
#-------------------------------------------------

QT       += core gui network

LIBS     += "C:/Users/Jimmy White/Desktop/SSH/build-SSH-Desktop_Qt_5_4_0_MinGW_32bit-Release/release/QSsh.dll"
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SSH
TEMPLATE = app

RC_FILE = linux.rc
SOURCES += main.cpp\
        mainwindow.cpp \
    myssh.cpp \
    form.cpp

HEADERS  += mainwindow.h \
    myssh.h \
    form.h

FORMS    += mainwindow.ui \
    form.ui
