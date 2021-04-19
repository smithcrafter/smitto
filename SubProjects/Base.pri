#Data.pro.pri

HEADERS += \
	$$PWD/../Source/Base/DatabaseConfig.h \
	$$PWD/../Source/Base/Service.h \

SOURCES += \
	$$PWD/../Source/Base/DatabaseConfig.cpp \
	$$PWD/../Source/Base/Service.cpp \

contains(QT, gui){
HEADERS += \
	$$PWD/../Source/Base/BaseQtApp.h \

SOURCES += \
	$$PWD/../Source/Base/BaseQtApp.cpp \
}
