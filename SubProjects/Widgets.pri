#Widgets.pro.pri

HEADERS += \
	$$PWD/../Source/Widgets/LogLabelsListWidget.h \
	$$ROOT_DIR/Source/Widgets/MenuStackedWidget.h \
	$$ROOT_DIR/Source/Widgets/LoginBaseWidget.h \
	$$ROOT_DIR/Source/Widgets/ServiceStatusWidget.h \
	$$ROOT_DIR/Source/Widgets/CustomTitleWidget.h \

SOURCES += \
	$$PWD/../Source/Widgets/LogLabelsListWidget.cpp \
	$$ROOT_DIR/Source/Widgets/MenuStackedWidget.cpp \
	$$ROOT_DIR/Source/Widgets/LoginBaseWidget.cpp \
	$$ROOT_DIR/Source/Widgets/ServiceStatusWidget.cpp \
	$$ROOT_DIR/Source/Widgets/CustomTitleWidget.cpp \

# ItemDelegate

SOURCES += \
	$$ROOT_DIR/Source/Widgets/ItemDelegate/RichTextDelegate.cpp \

HEADERS += \
	$$ROOT_DIR/Source/Widgets/ItemDelegate/RichTextDelegate.h \

# ProxyStyles

SOURCES += \
	$$ROOT_DIR/Source/Widgets/ProxyStyles/HorizontalWestTabStyle.cpp \

HEADERS += \
	$$ROOT_DIR/Source/Widgets/ProxyStyles/HorizontalWestTabStyle.h \
