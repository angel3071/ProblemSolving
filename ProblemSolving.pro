#-------------------------------------------------
#
# Project created by QtCreator 2015-04-08T17:03:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProblemSolving
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    deepsearchfirst.cpp \
    breadthsearchfirst.cpp \
    deeplimitedsearch.cpp \
    astar.cpp \
    idastar.cpp

HEADERS  += mainwindow.h \
    deepsearchfirst.h \
    breadthsearchfirst.h \
    deeplimitedsearch.h \
    astar.h \
    idastar.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
