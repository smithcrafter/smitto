#Widgets.pro.pri

HEADERS += \
	$$PWD/../Source/Widgets/LogLabelsListWidget.h \
	$$PWD/../Source/Widgets/LoginDesktopWidget.h \
	$$PWD/../Source/Widgets/MenuStackedWidget.h \
	$$PWD/../Source/Widgets/ServiceStatusWidget.h \
	$$PWD/../Source/Widgets/CustomTitleWidget.h \
	$$PWD/../Source/Widgets/AuthorizationMobileWidgets.h \
	$$PWD/../Source/Widgets/MobileScrollArea.h \
	$$PWD/../Source/Widgets/ToogleWidget.h \
    $$PWD/../Source/Widgets/PinWidget.h \

SOURCES += \
	$$PWD/../Source/Widgets/LogLabelsListWidget.cpp \
	$$PWD/../Source/Widgets/LoginDesktopWidget.cpp \
	$$PWD/../Source/Widgets/MenuStackedWidget.cpp \
	$$PWD/../Source/Widgets/ServiceStatusWidget.cpp \
	$$PWD/../Source/Widgets/CustomTitleWidget.cpp \
	$$PWD/../Source/Widgets/AuthorizationMobileWidgets.cpp \
	$$PWD/../Source/Widgets/MobileScrollArea.cpp \
	$$PWD/../Source/Widgets/ToogleWidget.cpp \
    $$PWD/../Source/Widgets/PinWidget.cpp \

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
