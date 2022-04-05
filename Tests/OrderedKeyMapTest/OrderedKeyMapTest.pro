QT -= gui

CONFIG += console
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -std=c++20

INCLUDEPATH += ../../Source
HEADERS += ../../Source/Algo/OrderedKeyMap.hpp
SOURCES +=  main.cpp
