#Data.pro.pri

HEADERS += \
    $$PWD/../Source/Base/BaseQtCoreApp.h \
	$$PWD/../Source/Base/DatabaseConfig.h \

SOURCES += \
    $$PWD/../Source/Base/BaseQtCoreApp.cpp \
	$$PWD/../Source/Base/DatabaseConfig.cpp \

contains(QT, gui){
HEADERS += \
	$$PWD/../Source/Base/BaseQtApp.h \
	$$PWD/../Source/Base/LibLoaderWidget.h \

SOURCES += \
	$$PWD/../Source/Base/BaseQtApp.cpp \
	$$PWD/../Source/Base/LibLoaderWidget.cpp \
}
