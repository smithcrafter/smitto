#Widgets.pro.pri

HEADERS += \
	$$PWD/../Source/Widgets/LogLabelsListWidget.h \
	$$PWD/../Source/Widgets/MenuStackedWidget.h \
	$$PWD/../Source/Widgets/LoginBaseWidget.h \
	$$PWD/../Source/Widgets/ServiceStatusWidget.h \
	$$PWD/../Source/Widgets/CustomTitleWidget.h \

SOURCES += \
	$$PWD/../Source/Widgets/LogLabelsListWidget.cpp \
	$$PWD/../Source/Widgets/MenuStackedWidget.cpp \
	$$PWD/../Source/Widgets/LoginBaseWidget.cpp \
	$$PWD/../Source/Widgets/ServiceStatusWidget.cpp \
	$$PWD/../Source/Widgets/CustomTitleWidget.cpp \

# ItemDelegate

SOURCES += \
	$$PWD/../Source/Widgets/ItemDelegate/RichTextDelegate.cpp \

HEADERS += \
	$$PWD/../Source/Widgets/ItemDelegate/RichTextDelegate.h \

# ProxyStyles

SOURCES += \
	$$PWD/../Source/Widgets/ProxyStyles/HorizontalWestTabStyle.cpp \

HEADERS += \
	$$PWD/../Source/Widgets/ProxyStyles/HorizontalWestTabStyle.h \
