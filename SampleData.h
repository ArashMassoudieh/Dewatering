#ifndef SAMPLEDATA_H
#define SAMPLEDATA_H

#include <QVector>
#include <QJsonArray>
#include <QJsonObject>

class DataSet;

class SampleData {
public:
    // Constants
    const double GramtoLb = 0.002204623;
    const double GramtoTon = 1.10231E-06;
    const double Cup_Diameter_to_in = 3.95;
    const double Cup_Area = 7.91E-03;
    const double Cup_Loading = 6.32;
    const double TSAssumed = 3.50;
    const double Polymer_Solution = 0.25;
        

    
    // Variables
    DataSet* parent; 
    QString Sample_Number;
    double Polymer_Dose;
    double Sludge_Weight;
    double Polymer_Before;
    double Polymer_After;
    double Sieve_Weight;
    double Bucket_Weight;
    double Sieve_plus_Wet_Solids_Weight;
    double Bucket_Filtrate;
    double Capture_Efficiency;
    
    QVector<double> FoilTray_plus_Filter_Weight;
    QVector<double> CST_Sludge;
    QVector<double> CST_Supernatant;
    QVector<double> Sample_Volume; 
    QVector<double> After_103; 

    double Dilution_Factor;
    QVector<double> Foil_Tray; 
    double Tolerance; 
    double Tolerance2; 


    // Default Constructor
    SampleData();

    // Copy Constructor
    SampleData(const SampleData& other);

    // Assignment Operator
    SampleData& operator=(const SampleData& other);

    // Destructor
    ~SampleData();

    double Calculated_Polymer_Added();
    double Actual_Belt_Filter_Press_before_PD_TS();
    double TS_percent();


    //Utility functions
    QJsonArray vectorToJsonArray(const QVector<double>& vec) const;
    QJsonObject toJson() const;

};



#endif // SAMPLEDATA_H
