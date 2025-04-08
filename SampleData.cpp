#include "SampleData.h"
#include "DataSet.h"

SampleData::SampleData() : Polymer_Dose(0.0), Sludge_Weight(0.0), Polymer_Before(0.0), Polymer_After(0.0),
Sieve_Weight(0.0), Bucket_Weight(0.0), Sieve_plus_Wet_Solids_Weight(0.0),
Bucket_Filtrate(0.0), Capture_Efficiency(0.0), Dilution_Factor(0.0),
Tolerance(0.0), Tolerance2(0.0), Sample_Number("1")
{

}


SampleData::SampleData(const SampleData& other) //Copy Constructor
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
    After_103_cake(other.After_103_cake),
    After_103_filtrate(other.After_103_filtrate),
    After_550_cake(other.After_550_cake),
    After_550_filtrate(other.After_550_filtrate),
    Dilution_Factor(other.Dilution_Factor),
    Tray_plus_Sample(other.Tray_plus_Sample),
    Foil_Tray(other.Foil_Tray),
    Tolerance(other.Tolerance),
    Tolerance2(other.Tolerance2),
    Sample_Number(other.Sample_Number)
    {


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
        After_103_cake = other.After_103_cake;
        After_103_filtrate = other.After_103_filtrate;
        After_550_cake = other.After_550_cake;
        After_550_filtrate = other.After_550_filtrate;
        Dilution_Factor = other.Dilution_Factor;
        Foil_Tray = other.Foil_Tray;
        Tolerance = other.Tolerance;
        Tolerance2 = other.Tolerance2;
        Sample_Number = other.Sample_Number;
        Tray_plus_Sample = other.Tray_plus_Sample;
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
    return 0.0;
}

QVector<double> SampleData::TS_percent() const
{
    QVector<double> out(After_103_cake.size());
    for (int i = 0; i < After_103_cake.size(); i++)
    {
        out[i] = (After_103_cake[i] - Foil_Tray[i]) * 100.0 / (Tray_plus_Sample[i] - Foil_Tray[i]);
    }
    return out; 
}

QVector<double> SampleData::TSS() const
{
    QVector<double> out(After_103_filtrate.size());
    for (int i = 0; i < After_103_filtrate.size(); i++)
    {
        out[i] = (After_103_filtrate[i] - Foil_Tray[i]) * 1000.0 /( Dilution_Factor - Sample_Volume[i]);
       
    }
    return out;
}
QVector<double> SampleData::VSS() const
{
    QVector<double> out(After_550_filtrate.size());
    for (int i = 0; i < After_550_filtrate.size(); i++)
    {
        out[i] = (After_550_filtrate[i] - After_103_filtrate[i]) / (Sample_Volume[i] *1000000.0);

    }
    return out;
}

double SampleData::Actual_Polymer_Added()
{
    return Polymer_After - Polymer_Before;
}

// Function to convert to QJsonObject
QJsonObject SampleData::toJson() const {
    QJsonObject json;

    // Convert primitive data types
    json["Sample_Number"] = Sample_Number;
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
    json["After_103_cake"] = vectorToJsonArray(After_103_cake);
    json["After_103_filtrate"] = vectorToJsonArray(After_103_filtrate);
    json["After_550_cake"] = vectorToJsonArray(After_550_cake);
    json["After_550_filtrate"] = vectorToJsonArray(After_550_filtrate);
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

QMap<QString, QVector<double>> SampleData::VariablesToMap()
{
    QMap<QString, QVector<double>> out;

    // Convert primitive data types
    out["Sample_Number"].append(Sample_Number.toDouble());
    out["Polymer_Dose"].append(Polymer_Dose);
    out["Sludge_Weight"].append(Sludge_Weight);
    out["Polymer_Before"].append(Polymer_Before);
    out["Polymer_After"].append(Polymer_After);
    out["Sieve_Weight"].append(Sieve_Weight);
    out["Bucket_Weight"].append(Bucket_Weight);
    out["Sieve_plus_Wet_Solids_Weight"].append(Sieve_plus_Wet_Solids_Weight);
    out["Bucket_Filtrate"].append(Bucket_Filtrate);
    out["Capture_Efficiency"].append(Capture_Efficiency);
    out["Dilution_Factor"].append(Dilution_Factor);
    out["Tolerance"].append(Tolerance);
    out["Tolerance2"].append(Tolerance2);

    // Convert QVector<double> to QJsonArray using the helper function
    out["FoilTray_plus_Filter_Weight"] = FoilTray_plus_Filter_Weight;
    out["CST_Sludge"] = CST_Sludge;
    out["CST_Supernatant"] = CST_Supernatant;
    out["Sample_Volume"] = Sample_Volume;
    out["After_103_cake"] = After_103_cake;
    out["After_103_filtrate"] = After_103_filtrate;
    out["After_550_cake"] = After_550_cake;
    out["After_550_filtrate"] = After_550_filtrate;
    out["Foil_Tray"] = Foil_Tray;

    return out;
}

double SampleData::TS() const
{
    return Average(TSS());
}
double SampleData::VS() const
{
    return Average(VSS());
}
double Average(const QVector<double>& values)
{
    double sum = 0; 
    for (int i = 0; i < values.count(); i++)
    {
        sum += values[i];
    }
    return sum / double(values.count());
}