#include "SludgeAnalyzer.h"
#include "xlsxdocument.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include "DataSet.h"


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

    QXlsx::Document xlsx(filePath);

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
        
        //Reading data related to the day of the experiment
        dummydataset.Belt_No = xlsx.read("B8").toString();
        dummydataset.Sludge_Flow = xlsx.read("B10").toDouble(); 

        //Reading data related to samples
        for (int i = 0; i < 6; i++)
        {
            SampleData datapoint;
            int j = xlsx.read(33+i, 1).toInt();
            datapoint.Polymer_Dose = xlsx.read(33 + i, 2).toDouble();
            // continue with all data

            dummydataset.append(datapoint);

            
        }
    }
    else {
        qDebug() << "Failed to load the file.";
    
    }

}

SludgeAnalyzer::~SludgeAnalyzer()
{}
