#ifndef SAMPLEDATA_H
#define SAMPLEDATA_H

#include <QVector>

class SampleData {
public:
    // Variables
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
};

#endif // SAMPLEDATA_H
