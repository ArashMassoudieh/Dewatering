/********************************************************************************
** Form generated from reading UI file 'SludgeAnalyzer.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLUDGEANALYZER_H
#define UI_SLUDGEANALYZER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SludgeAnalyzerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SludgeAnalyzerClass)
    {
        if (SludgeAnalyzerClass->objectName().isEmpty())
            SludgeAnalyzerClass->setObjectName("SludgeAnalyzerClass");
        SludgeAnalyzerClass->resize(600, 400);
        menuBar = new QMenuBar(SludgeAnalyzerClass);
        menuBar->setObjectName("menuBar");
        SludgeAnalyzerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SludgeAnalyzerClass);
        mainToolBar->setObjectName("mainToolBar");
        SludgeAnalyzerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SludgeAnalyzerClass);
        centralWidget->setObjectName("centralWidget");
        SludgeAnalyzerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SludgeAnalyzerClass);
        statusBar->setObjectName("statusBar");
        SludgeAnalyzerClass->setStatusBar(statusBar);

        retranslateUi(SludgeAnalyzerClass);

        QMetaObject::connectSlotsByName(SludgeAnalyzerClass);
    } // setupUi

    void retranslateUi(QMainWindow *SludgeAnalyzerClass)
    {
        SludgeAnalyzerClass->setWindowTitle(QCoreApplication::translate("SludgeAnalyzerClass", "SludgeAnalyzer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SludgeAnalyzerClass: public Ui_SludgeAnalyzerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLUDGEANALYZER_H
