#-------------------------------------------------
#
# Project created by QtCreator 2015-12-02T18:00:52
#
#-------------------------------------------------

QT       += core gui

CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graph
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    compil_widget.cpp \
    buttons.cpp \
    status.cpp \
    twopointsalhr.cpp \
    diametr.cpp \
    point.cpp \
    new_workspace.cpp \
    view.cpp \
    scene.cpp \
    floyd_warshall_alhorythm.cpp \
    bellman_ford_algorythm.cpp \
    line_item.cpp \
    text_item.cpp \
    simulated_annealing.cpp

HEADERS  += mainwindow.h \
    compil_widget.h \
    buttons.h \
    status.h \
    twopointsalhr.h \
    diametr.h \
    point.h \
    new_workspace.h \
    view.h \
    scene.h \
    floyd_warshall_alhorythm.h \
    bellman_ford_algorythm.h \
    line_item.h \
    text_item.h \
    simulated_annealing.h

FORMS    += mainwindow.ui

DISTFILES += \
    TODO \
    TODO
