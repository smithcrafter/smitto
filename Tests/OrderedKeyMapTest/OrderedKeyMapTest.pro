QT -= gui

CONFIG += console
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -std=c++20
QMAKE_CXXFLAGS += -Wno-unused-parameter


SOURCES +=  main.cpp

RAMIO_DIR = $$PWD/../../../Ramio/
SMITTO_DIR = $$PWD/../../../Smitto/

INCLUDEPATH		+= $$RAMIO_DIR/Include  $$RAMIO_DIR/Source  $$SMITTO_DIR/Include  $$SMITTO_DIR/Source

unix {
LIBS += "-L$$RAMIO_DIR/Lib" -lRamio-core
LIBS += "-L$$SMITTO_DIR/Lib" -lSmitto-core
}
