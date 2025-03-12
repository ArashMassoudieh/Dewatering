QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Utilities/Matrix.cpp \
    ../Utilities/Matrix_arma.cpp \
    ../Utilities/QuickSort.cpp \
    ../Utilities/Utilities.cpp \
    ../Utilities/Vector.cpp \
    ../Utilities/Vector_arma.cpp \
    DataSet.cpp \
    SampleData.cpp \
    SludgeAnalyzer.cpp \
    datasetcollection.cpp \
    fitfunction.cpp \
    main.cpp \
    treemodel.cpp \
    treeview.cpp

HEADERS += \
    ../Utilities/BTC.h \
    ../Utilities/BTC.hpp \
    ../Utilities/BTCSet.h \
    ../Utilities/BTCSet.hpp \
    ../Utilities/Matrix.h \
    ../Utilities/Matrix_arma.h \
    ../Utilities/QuickSort.h \
    ../Utilities/Utilities.h \
    ../Utilities/Vector.h \
    ../Utilities/Vector_arma.h \
    DataSet.h \
    SampleData.h \
    SludgeAnalyzer.h \
    datasetcollection.h \
    fitfunction.h \
    treemodel.h \
    treeview.h

FORMS += \
    SludgeAnalyzer.ui

INCLUDEPATH += ../QXlsx/QXlsx/header
INCLUDEPATH += ../Utilities

LIBS += /home/arash/Projects/QXlsx/libQXlsx.a

DEFINES += ARMA_USE_LAPACK ARMA_USE_BLAS
LIBS += -larmadillo -llapack -lblas -lgsl

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
