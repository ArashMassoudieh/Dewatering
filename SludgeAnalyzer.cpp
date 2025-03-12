#include "SludgeAnalyzer.h"
#include "xlsxdocument.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include "DataSet.h"
#include "ExpressionCalculator.h"
#include "fitfunction.h"
#include "datasetcollection.h"
#include <QTreeView>
#include "treemodel.h"
#include <QScreen>
#include "treeview.h"

SludgeAnalyzer::SludgeAnalyzer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QString filePath = QFileDialog::getOpenFileName(
        nullptr,                                // Parent widget (nullptr for none)
        "Open File",                           // Dialog title
        QDir::homePath(),                      // Initial directory
        "Text Files (*.xlsx);;All Files (*)"    // File filters
    );

    // Check if a file was selected
    DataSet dummydataset; 
    
    if (!filePath.isEmpty()) {
        qDebug() << "Selected file:" << filePath;
    }
    else {
        qDebug() << "No file selected.";
    }

    DataSetCollection* data = new (DataSetCollection);

    data->OpenExcel(filePath);
    data->SavetoJsonDocument("AllData.json");

    TreeModel *model = new TreeModel(data);
    TreeView *treeview = new TreeView(this);
    treeview->setModel(model);
    treeview->expandAll();

    ui.horizontalLayout->addWidget(treeview);






    QXlsx::Document xlsx(filePath);

    QStringList sheets = xlsx.sheetNames();
    qDebug() << "Available Sheets:" << sheets;

    xlsx.selectSheet("01_23_2025");
    if (xlsx.load()) {
        qDebug() << "File loaded successfully.";

        // Read a cell value
        QVariant value = xlsx.read("A1");
        if (value.isValid()) {
            qDebug() << "Value in A1:" << value.toString();
        }
        else {
            qDebug() << "Cell A1 is empty.";
        }
        
        QVariant valueB1 = xlsx.read("B1");
        qDebug() << "Value in B1" << valueB1; 
        //Reading data related to the day of the experiment
        dummydataset.Belt_No = xlsx.read("B8").toString();
        dummydataset.Sludge_Flow = xlsx.read("B10").toDouble(); 

        //Reading data related to samples
        for (int i = 0; i < 6; i++)
        {
            SampleData datapoint;
            int j = xlsx.read(33+i, 1).toInt();
            datapoint.Polymer_Dose = xlsx.read(33 + i, 4).toDouble();
            datapoint.Sludge_Weight = xlsx.read(33 + i, 4).toDouble();
            datapoint.Polymer_Before = xlsx.read(33 + i, 4).toDouble();
            datapoint.Polymer_After = xlsx.read(33 + i, 4).toDouble();
            datapoint.Sieve_Weight = xlsx.read(33 + i, 4).toDouble();
            datapoint.Bucket_Weight = xlsx.read(33 + i, 4).toDouble();

            // continue with all data

            dummydataset.Append(datapoint);

            
        }
    }
    else {
        qDebug() << "Failed to load the file.";
    
    }

}

SludgeAnalyzer::~SludgeAnalyzer()
{}
