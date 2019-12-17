#-------------------------------------------------
#
# Project created by QtCreator 2016-01-31T00:45:25
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
CONFIG   += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtMusicPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    note.cpp \
    notelist.cpp \
    playlist.cpp \
    track.cpp

HEADERS  += mainwindow.h \
    note.h \
    notelist.h \
    playlist.h \
    track.h \
    utils.h

FORMS    += mainwindow.ui
