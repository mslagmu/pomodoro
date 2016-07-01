#-------------------------------------------------
#
# Project created by QtCreator 2016-06-30T10:29:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pomodoro
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    taskslist.cpp

HEADERS  += mainwindow.h \
    taskslist.h

FORMS    += mainwindow.ui
