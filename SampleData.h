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
        
    void setParent(DataSet* p) { parent = p; }
    DataSet* getParent() const { return parent; }
    
    // Variables
    
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
    double Dilution_Factor;
    double Tolerance;
    double Tolerance2;

    
    QVector<double> FoilTray_plus_Filter_Weight;
    QVector<double> CST_Sludge;
    QVector<double> CST_Supernatant;
    QVector<double> After_103_cake; 
    QVector<double> After_103_filtrate;
    QVector<double> Tray_plus_Sample; 
    QVector<double> After_550_cake; 
    QVector<double> After_550_filtrate;
    QVector<double> Foil_Tray;
	QVector<double> SampleVolume;
    
    
    QMap<QString, QVector<double>> VariablesToMap(); 

    // Default Constructor
    SampleData();

    // Copy Constructor
    SampleData(const SampleData& other);

    // Assignment Operator
    SampleData& operator=(const SampleData& other);

    // Destructor
    ~SampleData();

    double Calculated_Polymer_Added() const;
    double Actual_Belt_Filter_Press_before_PD_TS() const;
    double Actual_Polymer_Added() const;
    double Actual_Polymer_Added_lb_per_Ton() const;
    double TSS_Avg() const;
    double VSS_Avg() const;
    double TS_Avg() const;
    double VS_Avg() const;
    double Filtered_Solids() const;
    double Filtrate() const;
    double Estimated_TSp_of_Wet_Solids_on_frabic() const; 
    double TargetWSinCup() const;
    double CST_Sludge_Avg() const;
    double CST_Supernatant_Avg() const;
    double Lab_Filtrate_TSS() const;

    QVector<double> TS_percent() const;
    QVector<double> TSS() const;
    QVector<double> VSS() const;
    QVector<double> TS() const; 
    QVector<double> VS() const;
    

    //Utility functions
    QJsonArray vectorToJsonArray(const QVector<double>& vec) const;
    QJsonObject toJson() const;
private: 
    DataSet* parent = nullptr;

};

double Average(const QVector<double>& values);
unsigned int minsize(const QVector<double>& vec1, const QVector<double>& vec2);
unsigned int minsize(const QVector<double>& vec1, const QVector<double>& vec2, const QVector<double>& vec3);



#endif // SAMPLEDATA_H
