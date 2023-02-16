QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountitem.cpp \
    addfrienddialog.cpp \
    chatwidget.cpp \
    clientexceptrion.cpp \
    createdialog.cpp \
    main.cpp \
    loginwidget.cpp \
    mainwidget.cpp \
    messagedatamanager.cpp \
    notice.cpp \
    selfinformation.cpp \
    tcpsocketmanager.cpp

HEADERS += \
    accountitem.h \
    addfrienddialog.h \
    chatwidget.h \
    clientexceptrion.h \
    createdialog.h \
    loginwidget.h \
    mainwidget.h \
    messagedatamanager.h \
    notice.h \
    selfinformation.h \
    tcpsocketmanager.h

FORMS += \
    accountitem.ui \
    addfrienddialog.ui \
    chatwidget.ui \
    createdialog.ui \
    loginwidget.ui \
    mainwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
