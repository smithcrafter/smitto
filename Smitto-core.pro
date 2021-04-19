#Ramio-core.pro

DEFINES += SMITTO_LIB

TARGET		= Smitto-core
VERSION		= 0.1.1
TEMPLATE	= lib
DESTDIR		= $$PWD/Lib

CONFIG+=console

RAMIO_DIR = $$PWD/../Ramio
INCLUDEPATH		+= . $$RAMIO_DIR/Include  $$RAMIO_DIR/Source

GITRAMIO_DIR = $$PWD/../ramio
INCLUDEPATH		+= . $$GITRAMIO_DIR/Include  $$GITRAMIO_DIR/Source

unix {
LIBS += "-L$$RAMIO_DIR/Lib" -lRamio-core
}
win32 {
LIBS += "-L$$RAMIO_DIR/Lib" -lRamio0
}

include(./SubProjects/Smitto.pri)

DISTFILES += \
	.gitignore \
	LICENSE \
	README.md \

message("DEFINES = " $$DEFINES)
