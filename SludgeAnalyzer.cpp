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


#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include "xlsxdocument.h"

SludgeAnalyzer::SludgeAnalyzer(QWidget* parent)
    : QMainWindow(parent)
{
    // ui.setupUi(this); // skip if you're not using the .ui layout

    QString filePath = QFileDialog::getOpenFileName(
        nullptr,
        "Open File",
        QDir::homePath(),
        "Text Files (*.xlsx);;All Files (*)"
    );

    data = new DataSetCollection();
    if (!filePath.isEmpty() && data->OpenExcel(filePath)) {
        qDebug() << "Selected file:" << filePath;
        data->SavetoJsonDocument("AllData.json");
    }
    else {
        qDebug() << "Failed to open Excel file.";
        return;
    }

    model = new TreeModel(data);
    treeview = new TreeView(this);
    treeview->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    treeview->setModel(model);

    tableview = new QTableView(this);
    tableview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QPushButton* exportButton = new QPushButton("Export to Excel", this);

    // Set up layouts
    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addWidget(treeview);
    hLayout->addWidget(tableview);

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayout);
    vLayout->addWidget(exportButton);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(vLayout);
    setCentralWidget(centralWidget);

    connect(treeview, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onItemDoubleClicked(QModelIndex)));
    connect(exportButton, &QPushButton::clicked, this, &SludgeAnalyzer::onExportClicked);
}

SludgeAnalyzer::~SludgeAnalyzer()
{

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

void SludgeAnalyzer::onItemDoubleClicked(QModelIndex index)
{
    QString key = model->data(index, Qt::DisplayRole).toString();
    qDebug() << "Parent: " << model->parent(index).data();
    qDebug() << "Clicked Key:" << key;
    QDate date = model->parent(index).data().toDate();
    qDebug() << date;
    if (data->value(date).LookupSampleNumber(key) == -1)
        return; 
    QMap<QString, QVector<double>> sampledata = data->value(date)[data->value(date).LookupSampleNumber(key)].VariablesToMap();
    TableModel* tableModel = new TableModel(sampledata);
    tableview->setModel(tableModel);
    
}