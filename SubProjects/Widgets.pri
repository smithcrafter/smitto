#Widgets.pro.pri

HEADERS += \
	$$ROOT_DIR/Source/Widgets/MenuStackedWidget.h \
	$$ROOT_DIR/Source/Widgets/LoginBaseWidget.h \

SOURCES += \
	$$ROOT_DIR/Source/Widgets/MenuStackedWidget.cpp \
	$$ROOT_DIR/Source/Widgets/LoginBaseWidget.cpp \

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
