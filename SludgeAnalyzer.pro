QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataSet.cpp \
    SampleData.cpp \
    SludgeAnalyzer.cpp \
    main.cpp

HEADERS += \
    DataSet.h \
    SampleData.h \
    SludgeAnalyzer.h

FORMS += \
    SludgeAnalyzer.ui

INCLUDEPATH += /Users/arash/Projects/QXlsx/QXlsx/header

macx {
    #sudo apt-get install libblas-dev liblapack-dev
    QMAKE_APPLE_DEVICE_ARCHS = arm64
    greaterThan(QT_MAJOR_VERSION, 5): LIBS += /Users/arash/Projects/QXlsx/install/debug/libQXlsx.a
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
