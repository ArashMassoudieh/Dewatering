#include "SampleData.h"
#include "DataSet.h"

SampleData::SampleData() : Polymer_Dose(0.0), Sludge_Weight(0.0), Polymer_Before(0.0), Polymer_After(0.0),
Sieve_Weight(0.0), Bucket_Weight(0.0), Sieve_plus_Wet_Solids_Weight(0.0),
Bucket_Filtrate(0.0), Capture_Efficiency(0.0), Dilution_Factor(0.0),
Tolerance(0.0), Tolerance2(0.0)
{

}


SampleData::SampleData(const SampleData& other)
    : Polymer_Dose(other.Polymer_Dose),
    Sludge_Weight(other.Sludge_Weight),
    Polymer_Before(other.Polymer_Before),
    Polymer_After(other.Polymer_After),
    Sieve_Weight(other.Sieve_Weight),
    Bucket_Weight(other.Bucket_Weight),
    Sieve_plus_Wet_Solids_Weight(other.Sieve_plus_Wet_Solids_Weight),
    Bucket_Filtrate(other.Bucket_Filtrate),
    Capture_Efficiency(other.Capture_Efficiency),
    FoilTray_plus_Filter_Weight(other.FoilTray_plus_Filter_Weight),
    CST_Sludge(other.CST_Sludge),
    CST_Supernatant(other.CST_Supernatant),
    Sample_Volume(other.Sample_Volume),
    After_103(other.After_103),
    Dilution_Factor(other.Dilution_Factor),
    Foil_Tray(other.Foil_Tray),
    Tolerance(other.Tolerance),
    Tolerance2(other.Tolerance2) {


}

SampleData& SampleData::operator=(const SampleData& other) {
    if (this != &other) {
        Polymer_Dose = other.Polymer_Dose;
        Sludge_Weight = other.Sludge_Weight;
        Polymer_Before = other.Polymer_Before;
        Polymer_After = other.Polymer_After;
        Sieve_Weight = other.Sieve_Weight;
        Bucket_Weight = other.Bucket_Weight;
        Sieve_plus_Wet_Solids_Weight = other.Sieve_plus_Wet_Solids_Weight;
        Bucket_Filtrate = other.Bucket_Filtrate;
        Capture_Efficiency = other.Capture_Efficiency;

        FoilTray_plus_Filter_Weight = other.FoilTray_plus_Filter_Weight;
        CST_Sludge = other.CST_Sludge;
        CST_Supernatant = other.CST_Supernatant;
        Sample_Volume = other.Sample_Volume;
        After_103 = other.After_103;

        Dilution_Factor = other.Dilution_Factor;
        Foil_Tray = other.Foil_Tray;
        Tolerance = other.Tolerance;
        Tolerance2 = other.Tolerance2;
    }
    return *this;
}

SampleData::~SampleData()
{

};

double SampleData::Calculated_Polymer_Added()
{
    return Polymer_Dose * Sludge_Weight * GramtoTon * Actual_Belt_Filter_Press_before_PD_TS() / (GramtoLb * Polymer_Solution);
}

double SampleData::Actual_Belt_Filter_Press_before_PD_TS()
{
    return parent->last().TS_percent(); 
}

double SampleData::TS_percent()
{
    return 0; //needs to be completed; 
}

// Function to convert to QJsonObject
QJsonObject SampleData::toJson() const {
    QJsonObject json;

    // Convert primitive data types
    json["Polymer_Dose"] = Polymer_Dose;
    json["Sludge_Weight"] = Sludge_Weight;
    json["Polymer_Before"] = Polymer_Before;
    json["Polymer_After"] = Polymer_After;
    json["Sieve_Weight"] = Sieve_Weight;
    json["Bucket_Weight"] = Bucket_Weight;
    json["Sieve_plus_Wet_Solids_Weight"] = Sieve_plus_Wet_Solids_Weight;
    json["Bucket_Filtrate"] = Bucket_Filtrate;
    json["Capture_Efficiency"] = Capture_Efficiency;
    json["Dilution_Factor"] = Dilution_Factor;
    json["Tolerance"] = Tolerance;
    json["Tolerance2"] = Tolerance2;

    // Convert QVector<double> to QJsonArray using the helper function
    json["FoilTray_plus_Filter_Weight"] = vectorToJsonArray(FoilTray_plus_Filter_Weight);
    json["CST_Sludge"] = vectorToJsonArray(CST_Sludge);
    json["CST_Supernatant"] = vectorToJsonArray(CST_Supernatant);
    json["Sample_Volume"] = vectorToJsonArray(Sample_Volume);
    json["After_103"] = vectorToJsonArray(After_103);
    json["Foil_Tray"] = vectorToJsonArray(Foil_Tray);

    return json;
}

// Helper function to convert QVector<double> to QJsonArray
QJsonArray SampleData::vectorToJsonArray(const QVector<double>& vec) const {
    QJsonArray array;
    for (int i = 0; i < vec.size(); ++i) {
        array.append(vec[i]);
    }
    return array;
}


