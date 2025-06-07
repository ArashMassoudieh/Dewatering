#include "SludgeAnalyzer.h"
#include "xlsxdocument.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include "DataSet.h"
#include "ExpressionCalculator.h"
#include "fitfunction.h"
#include "datasetcollection.h"
#include <QTableView>
#include "treemodel.h"
#include <QScreen>
#include "treeview.h"
#include "TableModel.h"
#include <QDate>
#include "fitfunction.h"


#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include "xlsxdocument.h"
#include "qplotwindow.h"
#include "ErrorList.h"
#include "DataSet.h"

SludgeAnalyzer::SludgeAnalyzer(QWidget* parent)
    : QMainWindow(parent)
{
    // ui.setupUi(this); // skip if you're not using the .ui layout

    resource_directory = qApp->applicationDirPath() + "/../../resources";

    

    
}

void SludgeAnalyzer::SetThreshold(double CST_threshold, double TSS_gradient_threshold)
{
    if (data)
    {
        data->SetCSTThreshold(CST_threshold);
        data->SetTSSGradientThreshold(TSS_gradient_threshold);
    }
}

SludgeAnalyzer::~SludgeAnalyzer()
{

}

bool SludgeAnalyzer::SetData(DataSetCollection* _data)
{
	this->data = _data;
    model = new TreeModel(data);
    treeview = new TreeView(this);
    treeview->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    treeview->setModel(model);

    tableview = new QTableView(this);
    tableview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    treeview->setContextMenuPolicy(Qt::CustomContextMenu);

    QPushButton* exportButton = new QPushButton("Export to Excel", this);
    QPushButton* exporttoJsonButton = new QPushButton("Export to Json", this);
    QPushButton* plotOPD = new QPushButton("Plot OPD", this);

    // Set up layouts
    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addWidget(treeview);
    hLayout->addWidget(tableview);

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayout);
    QHBoxLayout* bLayout = new QHBoxLayout();

    bLayout->addWidget(exportButton);
    bLayout->addWidget(exporttoJsonButton);
	bLayout->addWidget(plotOPD);
    vLayout->addLayout(bLayout);
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(vLayout);
    setCentralWidget(centralWidget);

    connect(treeview, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onItemDoubleClicked(QModelIndex)));
    connect(treeview, &QWidget::customContextMenuRequested, this, &SludgeAnalyzer::onTreeContextMenuRequested);
    connect(exportButton, &QPushButton::clicked, this, &SludgeAnalyzer::onExportClicked);
    connect(exporttoJsonButton, &QPushButton::clicked, this, &SludgeAnalyzer::onExporttoJsonClicked);
    connect(plotOPD, &QPushButton::clicked, this, &SludgeAnalyzer::onPlotOPD);
    return true;
}

void SludgeAnalyzer::onExportClicked()
{
	QString filePath = QFileDialog::getSaveFileName(
		nullptr,
		"Save File",
		QDir::homePath(),
		"Excel Files (*.xlsx);;All Files (*)"
	);
	if (!filePath.isEmpty()) {
		qDebug() << "Exporting to:" << filePath;
		data->ExportToExcel(filePath);
	}
	else {
		qDebug() << "No file selected for export.";
	}
}

void SludgeAnalyzer::onExporttoJsonClicked()
{
    QString filePath = QFileDialog::getSaveFileName(
        nullptr,
        "Save File",
        QDir::homePath(),
        "Json Files (*.json);;All Files (*)"
    );
    if (!filePath.isEmpty()) {
        qDebug() << "Exporting to:" << filePath;
        data->SavetoJsonDocument(filePath);
    }
    else {
        qDebug() << "No file selected for export.";
    }
}

void SludgeAnalyzer::onPlotOPD()
{
	QPlotWindow* plotter = new QPlotWindow(this);
    CTimeSeriesSet<double> plotitemset; 
    CTimeSeries<double> timeseries_H = data->GetOPDTimeSeries(CalculationMethod::OPD_Lookup);
	plotitemset.append(timeseries_H, "OPD_H");
	CTimeSeries<double> timeseries_I = data->GetOPDTimeSeries(CalculationMethod::OPD_Interpolation);
	plotitemset.append(timeseries_I, "OPD_I");
    /// Comment
	plotter->PlotData(plotitemset, true, QStringList()<<"dot"<<"dot");
	plotter->show();
	
}

void SludgeAnalyzer::onItemDoubleClicked(QModelIndex index)
{
    QString key = model->data(index, Qt::DisplayRole).toString();
	int level = getIndexLevel(index);
    qDebug() << "Parent: " << model->parent(index).data();
    qDebug() << "Clicked Key:" << key;
    if (level == 1) // Only proceed if the clicked item is at the correct level
    {
        QDate date = model->parent(index).data().toDate();
        qDebug() << date;
        if (data->value(date).LookupSampleNumber(key) == -1)
            return;
        QMap<QString, QVector<double>> sampledata = data->value(date)[data->value(date).LookupSampleNumber(key)].VariablesToMap();
        TableModel<QVector<double>>* tableModel = new TableModel(sampledata);
        tableview->setModel(tableModel);
    }
	else if (level == 0) // If the clicked item is at the date level
	{
		QDate date = model->data(index, Qt::DisplayRole).toDate();
		qDebug() << "Clicked Date:" << date;
		if (data->count(date) == 0)
			return;
		QMap<QString, QString> tabledata = data->value(date).VariablesToMap();
		TableModel<QString>* tableModel = new TableModel(tabledata);
		tableview->setModel(tableModel);
	}
	else
	{
		qDebug() << "Clicked item is not at the correct level.";
	}
    
}

int getIndexLevel(const QModelIndex& index)
{
    int level = 0;
    QModelIndex current = index;
    while (current.parent().isValid()) {
        current = current.parent();
        ++level;
    }
    return level;
}

void SludgeAnalyzer::onTreeContextMenuRequested(const QPoint& pos)
{
    QModelIndex index = treeview->indexAt(pos);
    if (!index.isValid())
        return;

    QString itemText = model->data(index, Qt::DisplayRole).toString();
    qDebug() << "Right-clicked item:" << itemText;
    
    QDate date = QDate::fromString(itemText.trimmed().simplified(), Qt::ISODate);
    qDebug() << date; 
    if (data->count(date) != 0)
    {
        QMenu contextMenu(this);
        QAction* exportAction = contextMenu.addAction("Export Sample");
        QAction* viewAction = contextMenu.addAction("View Sample");
        QAction* TSvsPolymerDose = contextMenu.addAction("Plot TS vs Polymer Dose");
        QAction* CSTSludgevsPolymerDose = contextMenu.addAction("Plot CST Sludge vs. Polymer Dose");
        QAction* TSSvsPolymerDose = contextMenu.addAction("Plot TSS vs. Polymer Dose");

        QAction* selectedAction = contextMenu.exec(treeview->viewport()->mapToGlobal(pos));

        if (selectedAction == TSvsPolymerDose) {
            QPlotWindow* plotter = new QPlotWindow(this);
            CTimeSeriesSet<double> plotitemset;
            CTimeSeries<double> plotitem;
            QVector<double> xvalues = data->value(date).ExtractVariable("Polymer_Dose");
            QVector<double> yvalues = data->value(date).ExtractVariable("TS_Avg");
            for (int i = 0; i < min(xvalues.size(), yvalues.size()); i++)
            {
				if (xvalues[i] != 0) // Skip zero values
                    plotitem.append(xvalues[i], yvalues[i]);
            }
            plotitemset.append(plotitem, "TS");
            
            FitFunction fitFunction;
            fitFunction.SetObservedData(plotitem); 
            fitFunction.SetFunctionForm(FunctionForm::expontialdeclining);
            result Result = fitFunction.Solve();
			            
			plotitemset.append(Result.predicted, "Fit: TS vs Polymer Dose");
            plotitemset.append(Result.derivative, "Fit: TS (derivative)");
            plotter->PlotData(plotitemset, false);
            plotter->show();

        }

        if (selectedAction == CSTSludgevsPolymerDose) {
            QPlotWindow* plotter = new QPlotWindow(this);
            CTimeSeriesSet<double> plotitemset;
            CTimeSeries<double> plotitem;
            QVector<double> xvalues = data->value(date).ExtractVariable("Actual_Polymer_Added_lb_per_Ton");
            QVector<double> yvalues = data->value(date).ExtractVariable("CST_Sludge_Avg");
            for (int i = 0; i < min(xvalues.size(), yvalues.size()); i++)
            {
                if (xvalues[i] != 0) // Skip zero values
                    plotitem.append(xvalues[i], yvalues[i]);
            }
            plotitemset.append(plotitem, "CST Sludge");
            FitFunction fitFunction;
			fitFunction.SetFunctionForm(FunctionForm::expontialdeclining);
            fitFunction.SetObservedData(plotitem);
            result Result = fitFunction.Solve();

            plotitemset.append(Result.predicted, "Fit: CST Sludge");
            plotitemset.append(Result.derivative, "Fit: CST Sludge (derivative)");

			
            QPair<double, double> OPD_point_H;
            QPair<double, double> OPD_point_I;
            OPD_point_I = data->value(date).OPD();
            OPD_point_H = data->value(date).OPD_Haydees_formula();

            CTimeSeries<double> plotitemOPD_H;
            plotitemOPD_H.append(plotitem.mint(), OPD_point_H.second);
            plotitemOPD_H.append(plotitem.maxt(), OPD_point_H.second);
            plotitemset.append(plotitemOPD_H, "CST Sludge @ OPH (H)");
            CTimeSeries<double> plotitemOPDvertical_H;
            plotitemOPDvertical_H.append(OPD_point_H.first, plotitem.minC());
            plotitemOPDvertical_H.append(OPD_point_H.first, plotitem.maxC());
            plotitemset.append(plotitemOPDvertical_H, "OPD (H)");

            CTimeSeries<double> plotitemOPD_I;
            plotitemOPD_I.append(plotitem.mint(), OPD_point_I.second);
            plotitemOPD_I.append(plotitem.maxt(), OPD_point_I.second);
            plotitemset.append(plotitemOPD_I, "CST Sludge @ OPH (I)");
            CTimeSeries<double> plotitemOPDvertical_I;
            plotitemOPDvertical_I.append(OPD_point_I.first, plotitem.minC());
            plotitemOPDvertical_I.append(OPD_point_I.first, plotitem.maxC());
            plotitemset.append(plotitemOPDvertical_I, "OPD (I)");


			QStringList styles = QStringList() << "dot" << "line" << "line" << "line" << "line";
            plotter->PlotData(plotitemset, false, styles);
            plotter->show();

        }

        if (selectedAction == TSSvsPolymerDose) {
            QPlotWindow* plotter = new QPlotWindow(this);
            CTimeSeriesSet<double> plotitemset;
            CTimeSeries<double> plotitem;
            QVector<double> xvalues = data->value(date).ExtractVariable("Polymer_Dose");
            QVector<double> yvalues = data->value(date).ExtractVariable("TSS_Avg");
            for (int i = 0; i < min(xvalues.size(), yvalues.size()); i++)
            {
                if (xvalues[i] != 0) // Skip zero values
                    plotitem.append(xvalues[i], yvalues[i]);
            }
			plotitemset.append(plotitem, "TSS");
            FitFunction fitFunction;
            fitFunction.SetObservedData(plotitem);
            fitFunction.SetFunctionForm(FunctionForm::expontialdeclining);
            result Result = fitFunction.Solve();

            plotitemset.append(Result.predicted, "Fit: TSS");
            plotitemset.append(Result.derivative, "Fit: TSS (derivative)");
            plotter->PlotData(plotitemset, false);
            plotter->show();

        }

        if (selectedAction == exportAction) {
            qDebug() << "Export triggered for" << itemText;
            // Handle export logic here
        }


        else if (selectedAction == viewAction) {
            qDebug() << "View triggered for" << itemText;
            // You could call onItemDoubleClicked(index) or custom view logic
            onItemDoubleClicked(index);
        }
    }
}