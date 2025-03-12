#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SludgeAnalyzer.h"
#include <QModelIndex>

class TreeModel;
class TreeView; 
class DataSetCollection; 
class QTableView; 

class SludgeAnalyzer : public QMainWindow
{
    Q_OBJECT

public:
    SludgeAnalyzer(QWidget *parent = nullptr);
    ~SludgeAnalyzer();

private:
    Ui::SludgeAnalyzerClass ui;
    TreeModel* model;
    TreeView*  treeview;
    QTableView* tableview;
    DataSetCollection* data;
public slots:
    void onItemDoubleClicked(QModelIndex index);
};
