#Ramio.pro.pri

contains(DEFINES, SMITTO_LIB) {
	DEFINES += TARGET_AUTHOR="\\\"Smithcoder\\\""
	DEFINES += TARGET_NAME="\\\"Smitto\\\""
} else {
	DEFINES += SMITTO_DIRECT
}

ROOT_DIR = $$PWD/..
INCLUDEPATH		+= $$ROOT_DIR/Source
INCLUDEPATH		+= $$ROOT_DIR/Include

QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS += -Wno-unused-parameter

QT		+= core xml sql network

contains(CONFIG, console) {
	DEFINES += CONSOLE_APP
	QT -= gui
} else {
	QT		+= gui widgets
}

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
	$$ROOT_DIR/Source/smitto.h \

#SOURCES += \
#	$$ROOT_DIR/Source/smitto.cpp \

include (Base.pri)
include (System.pri)
include (Data.pri)
include (BaseItems.pri)
include (Diagnostic.pri)
include (Services.pri)


contains(QT, gui){
	include(Gui.pri)
	include(Widgets.pri)
}
