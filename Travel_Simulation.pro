#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T20:13:44
#
#-------------------------------------------------


QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = Travel_Simulation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addtravellerdialog.cpp \
    choosewaydialog.cpp \
    filltimedialog.cpp \
    fillinfodialog.cpp \
    calendardialog.cpp \
    showiddialog.cpp \
    traveller.cpp \
    map.cpp \
    databaseoperations.cpp \
    aboutusdialog.cpp \
    backupdialog.cpp \
    restoredialog.cpp \
    choosecitydialog.cpp

HEADERS  += mainwindow.h \
    datastructure.h \
    addtravellerdialog.h \
    choosewaydialog.h \
    filltimedialog.h \
    fillinfodialog.h \
    calendardialog.h \
    showiddialog.h \
    traveller.h \
    map.h \
    aboutusdialog.h \
    backupdialog.h \
    restoredialog.h \
    choosecitydialog.h

FORMS    += mainwindow.ui \
    addtravellerdialog.ui \
    choosewaydialog.ui \
    filltimedialog.ui \
    fillinfodialog.ui \
    calendardialog.ui \
    showiddialog.ui \
    aboutusdialog.ui \
    backupdialog.ui \
    restoredialog.ui \
    choosecitydialog.ui


RESOURCES += \
    image.qrc \
    fileicon.qrc

DISTFILES +=


