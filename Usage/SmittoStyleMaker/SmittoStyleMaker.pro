QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DESTDIR		= $$PWD/../../Bin

INCLUDEPATH += ../../Source/

SOURCES += main.cpp \
	../../Source/Gui/SmittoColors.cpp \
    SmittoCSSMaker.cpp

HEADERS += \
	../../Source/Gui/SmittoColors.h \
    SmittoCSSMaker.h

