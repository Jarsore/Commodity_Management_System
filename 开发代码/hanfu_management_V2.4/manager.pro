QT       += core gui
QT       +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customer.cpp \
    logindialog.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    connection.h \
    customer.h \
    logindialog.h \
    widget.h

FORMS += \
    customer.ui \
    logindialog.ui \
    widget.ui

RC_ICONS = dute_favicon_32x32.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    resource/dute_favicon_32x32.ico

RESOURCES += \
    hanfu.qrc \
    ico_s.qrc \
    picture.qrc
