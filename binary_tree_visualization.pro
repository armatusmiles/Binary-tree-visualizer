#-------------------------------------------------
#
# Project created by QtCreator 2016-11-22T19:01:11
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = binary_tree_visualization
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    binarytree.cpp

HEADERS  += mainwindow.h \
    binarytree.h

FORMS    += mainwindow.ui

RESOURCES += \
    imeages.qrc
