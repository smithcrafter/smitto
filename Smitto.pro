#Ramio.pro

DEFINES += SMITTO_LIB

TARGET		= Smitto
VERSION		= 0.1.1
TEMPLATE	= lib
DESTDIR		= $$PWD/Lib

RAMIO_DIR = $$PWD/../Ramio
INCLUDEPATH		+= . $$RAMIO_DIR/Include  $$RAMIO_DIR/Source

unix {
LIBS += "-L$$RAMIO_DIR/Lib" -lRamio
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
