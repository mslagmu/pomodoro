#-------------------------------------------------
#
# Project created by QtCreator 2016-06-30T10:29:19
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pomodoro
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    taskslist.cpp \
    chrono.cpp

HEADERS  += mainwindow.h \
    taskslist.h \
    chrono.h \
    constants.h

FORMS    += mainwindow.ui \
    chrono.ui

RESOURCES += \
    resources.qrc
