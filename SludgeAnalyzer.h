#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SludgeAnalyzer.h"
#include <QModelIndex>
#include "BTC.h"

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
	bool SetData(DataSetCollection* data);
    QString resource_directory;
    QMap<QString, CTimeSeries<double>*> graphsClipboard = QMap<QString, CTimeSeries<double>*>();
    void SetThreshold(double CST_threshold, double TSS_gradient_threshold);
	
private:
    Ui::SludgeAnalyzerClass ui;
    TreeModel* model = nullptr;
    TreeView*  treeview = nullptr;
    QTableView* tableview = nullptr;
    DataSetCollection* data = nullptr;

public slots:
    void onItemDoubleClicked(QModelIndex index);
    void onExportClicked();
    void onExporttoJsonClicked();
    void onTreeContextMenuRequested(const QPoint& pos);
    void onPlotOPD();

};
