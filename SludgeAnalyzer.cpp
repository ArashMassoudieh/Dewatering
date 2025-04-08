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

    data = new DataSetCollection();

    data->OpenExcel(filePath);
    data->SavetoJsonDocument("AllData.json");

    model = new TreeModel(data);
    treeview = new TreeView(this);
    treeview->setModel(model);
    //treeview->expandAll();

    ui.horizontalLayout->addWidget(treeview);

    tableview = new QTableView(this);
    
    ui.horizontalLayout->addWidget(tableview);

    connect(treeview, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onItemDoubleClicked(QModelIndex)));
    
    QXlsx::Document xlsx(filePath);

    QStringList sheets = xlsx.sheetNames();
    qDebug() << "Available Sheets:" << sheets;

    
    if (xlsx.load()) {
        xlsx.selectSheet("01_23_2025");
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
            datapoint.Polymer_Dose = xlsx.read(33 + i, 2).toDouble();
            datapoint.Sludge_Weight = xlsx.read(33 + i, 4).toDouble();
            datapoint.Polymer_Before = xlsx.read(33 + i, 6).toDouble();
            datapoint.Polymer_After = xlsx.read(33 + i, 7).toDouble();
            datapoint.Sieve_Weight = xlsx.read(33 + i, 10).toDouble();
            datapoint.Bucket_Weight = xlsx.read(33 + i, 11).toDouble();
            datapoint.Sieve_plus_Wet_Solids_Weight = xlsx.read(33 + i, 12).toDouble();
            datapoint.Bucket_Filtrate = xlsx.read(33 + i, 13).toDouble();
            for (int j = 0; j < 5; j++)
            {
                if (xlsx.read(41 + i, 4 + j).isValid())
                {
                    datapoint.CST_Sludge.append(xlsx.read(41 + i, 4 + j).toDouble());
                }
            }
            for (int j = 0; j < 5; j++)
            {
                if (xlsx.read(41 + i, 9 + j).isValid())
                {
                    datapoint.CST_Supernatant.append(xlsx.read(41 + i, 9 + j).toDouble());
                }
            }
            
            //Foil Tray + Filter Weight
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(51 + i, 2 + j).isValid())
                {
                    datapoint.FoilTray_plus_Filter_Weight.append(xlsx.read(51 + i, 2 + j).toDouble());
                }
            }
            for (int j = 0; j < 2; j++)
            {    if (xlsx.read(76 + i, 2 + j).isValid())
                {
                    datapoint.FoilTray_plus_Filter_Weight.append(xlsx.read(76 + i, 2 + j).toDouble());
                }
            }


           // for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(51 + i, 4 + j).isValid())
                {
                    datapoint.Tray_plus_Sample.append(xlsx.read(51 + i, 4 + j).toDouble());
                }
            }
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(76 + i, 4 + j).isValid())
                {
                    datapoint.Tray_plus_Sample.append(xlsx.read(76 + i, 4 + j).toDouble());
                }
            }
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(51 + i, 4 + j).isValid())
                {
                    datapoint.Sample_Volume.append(xlsx.read(51 + i, 4 + j).toDouble());
                }
            }
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(76 + i, 4 + j).isValid())
                {
                    datapoint.Sample_Volume.append(xlsx.read(76 + i, 4 + j).toDouble());
                }
            }
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(51 + i, 6 + j).isValid())
                {
                    datapoint.After_103_filtrate.append(xlsx.read(51 + i, 6 + j).toDouble());
                }
            }
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(76 + i, 6 + j).isValid())
                {
                    datapoint.After_103_filtrate.append(xlsx.read(76 + i, 6 + j).toDouble());
                }
            }
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(51 + i, 12 + j).isValid())
                {
                    datapoint.After_550_filtrate.append(xlsx.read(51 + i, 12 + j).toDouble());
                }
            }
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(76 + i, 12 + j).isValid())
                {
                    datapoint.After_550_filtrate.append(xlsx.read(76 + i, 12 + j).toDouble());
                }
            }
            //Foil Tray (cake)
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(62 + i, 2 + j).isValid())
                {
                    datapoint.Foil_Tray.append(xlsx.read(62 + i, 2 + j).toDouble());
                }
            }
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(85 + i, 2 + j).isValid())
                {
                    datapoint.Foil_Tray.append(xlsx.read(85 + i, 2 + j).toDouble());
                }
            }
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(62 + i, 4 + j).isValid())
                {
                    datapoint.Tray_plus_Sample.append(xlsx.read(62 + i, 4 + j).toDouble());
                }
            }
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(85 + i, 4 + j).isValid())
                {
                    datapoint.Tray_plus_Sample.append(xlsx.read(85 + i, 4 + j).toDouble());
                }
            }
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(62 + i, 6 + j).isValid())
                {
                    datapoint.After_103_cake.append(xlsx.read(62 + i, 6 + j).toDouble());
                }
            }
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(85 + i, 6 + j).isValid())
                {
                    datapoint.After_103_cake.append(xlsx.read(85 + i, 6 + j).toDouble());
                }
            }
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(62 + i, 11 + j).isValid())
                {
                    datapoint.After_550_cake.append(xlsx.read(62 + i, 11 + j).toDouble());
                }
            }
            for (int j = 0; j < 2; j++)
            {
                if (xlsx.read(85 + i, 11 + j).isValid())
                {
                    datapoint.After_550_cake.append(xlsx.read(85 + i, 11 + j).toDouble());
                }
            }
            // continue with all data

            dummydataset.Append(datapoint);

            
        }
    }
    else {
        qDebug() << "Failed to load the file.";
    
    }
  
    
}

SludgeAnalyzer::~SludgeAnalyzer()
{

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