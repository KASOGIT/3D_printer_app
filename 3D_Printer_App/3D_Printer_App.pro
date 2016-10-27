#-------------------------------------------------
#
# Project created by QtCreator 2015-07-05T17:09:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3D_Printer_App
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myGLWidget_abstract.cpp \
    sceneobjects.cpp \
    trianglestl.cpp \
    pointstl.cpp \
    project.cpp \
    line.cpp \
    layer.cpp \
    slicer.cpp \
    moveobject.cpp \
    rotateobject.cpp \
    resizeobject.cpp

HEADERS  += mainwindow.h \
    myGLWidget_abstract.h \
    sceneobjects.h \
    trianglestl.h \
    pointstl.h \
    project.h \
    line.h \
    layer.h \
    slicer.h \
    moveobject.h \
    rotateobject.h \
    resizeobject.h
