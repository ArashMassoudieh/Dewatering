#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SludgeAnalyzer.h"

class SludgeAnalyzer : public QMainWindow
{
    Q_OBJECT

public:
    SludgeAnalyzer(QWidget *parent = nullptr);
    ~SludgeAnalyzer();

private:
    Ui::SludgeAnalyzerClass ui;
};
