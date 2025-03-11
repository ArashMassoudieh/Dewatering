#include "SludgeAnalyzer.h"
#include "xlsxdocument.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include "DataSet.h"
#include "ExpressionCalculator.h"
#include "fitfunction.h"

SludgeAnalyzer::SludgeAnalyzer(QWidget *parent)
    : QMainWindow(parent)
{
    QMap<QString, double> parameters; 
    parameters["weight"] = 1000;
    parameters["volume"] = 2000;
    parameters["x"] = 5;
    ExpressionCalculator exprcalc("weight/volume+log(x)");
    double output = exprcalc.calc(&parameters);
    
    FitFunction fitfunc;
    CTimeSeries<double> observed_data;
    observed_data.append(10,1.9);
    observed_data.append(20,3.8);
    observed_data.append(30,4.5);
    observed_data.append(40,4.8);
    observed_data.append(50,4.9);
    observed_data.append(60,4.9);
    observed_data.append(70,4.9);

    fitfunc.SetObservedData(observed_data);

    CVector_arma params(3);
    params[0] = 8;
    params[1] = 0.3;
    params[2] = 2;

    CVector_arma optimized_params = fitfunc.SolveLevenBerg_Marquardt(params);
    optimized_params.writetofile("params.txt");


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
