TARGET = emtumble
CONFIG += c++14
VERSION = 0.2.0
DEFINES += VERSION_STRING=\\\"$${VERSION}\\\"

QT += core gui widgets
QMAKE_CXX      = g++-6
QMAKE_LINK     = g++-6
QMAKE_CXXFLAGS += -std=c++14 -Wall -Wextra -Wshadow -g 
QMAKE_CXXFLAGS -= -stdlib=libc++
QMAKE_LFLAGS   -= -stdlib=libc++

# http://stackoverflow.com/questions/2580934
DESTDIR     = bin
OBJECTS_DIR = obj
MOC_DIR     = obj
SOURCE_DIR  = .

INCLUDEPATH    += $SOURCE_DIR
SOURCES        += $$files(*.cpp, true)
HEADERS        += ui/mainwindow.h
# HEADERS        += ui/BoardGraphicsScene.h
# HEADERS        += ui/ScalableGraphicsView.h

mac {
  CONFIG -= app_bundle
}
