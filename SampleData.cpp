#include "SampleData.h"
#include "DataSet.h"
#include <algorithm>

SampleData::SampleData() : Polymer_Dose(0.0), Sludge_Weight(0.0), Polymer_Before(0.0), Polymer_After(0.0),
Sieve_Weight(0.0), Bucket_Weight(0.0), Sieve_plus_Wet_Solids_Weight(0.0),
Bucket_Filtrate(0.0), Capture_Efficiency(0.0), Dilution_Factor(0.0),
Tolerance(0.0), Tolerance2(0.0), SampleVolume(0.0), Sample_Number("1")
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
	SampleVolume(other.SampleVolume),
    FoilTray_plus_Filter_Weight(other.FoilTray_plus_Filter_Weight),
    CST_Sludge(other.CST_Sludge),
    CST_Supernatant(other.CST_Supernatant),
    After_103_cake(other.After_103_cake),
    After_103_filtrate(other.After_103_filtrate),
    After_550_cake(other.After_550_cake),
    After_550_filtrate(other.After_550_filtrate),
    Dilution_Factor(other.Dilution_Factor),
    Tray_plus_Sample(other.Tray_plus_Sample),
    Foil_Tray(other.Foil_Tray),
    Tolerance(other.Tolerance),
    Tolerance2(other.Tolerance2),
    Sample_Number(other.Sample_Number){
   
     
        parent = other.parent; 
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
		SampleVolume = other.SampleVolume;

        FoilTray_plus_Filter_Weight = other.FoilTray_plus_Filter_Weight;
        CST_Sludge = other.CST_Sludge;
        CST_Supernatant = other.CST_Supernatant;
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
        parent = other.parent;
        
    }
    return *this;
}

SampleData::~SampleData()
{

};

double SampleData::Calculated_Polymer_Added() const
{
    return Polymer_Dose * Sludge_Weight * GramtoTon * Actual_Belt_Filter_Press_before_PD_TS() / (GramtoLb * Polymer_Solution);
}

double SampleData::Actual_Belt_Filter_Press_before_PD_TS() const 
{
    return parent->BFPTS_percent;
}

QVector<double> SampleData::TS_percent() const
{
    QVector<double> out(minsize(After_103_cake,Foil_Tray,Tray_plus_Sample));
    for (int i = 0; i < After_103_cake.size(); i++)
    {
        out[i] = (After_103_cake[i] - Foil_Tray[i]) * 100.0 / (Tray_plus_Sample[i] - Foil_Tray[i]);
    }
    return out; 
}

QVector<double> SampleData::TSS() const
{
    QVector<double> out(minsize(After_103_filtrate, FoilTray_plus_Filter_Weight, SampleVolume));

    for (int i = 0; i < out.size(); i++)
    {
        out[i] = (After_103_filtrate[i] - FoilTray_plus_Filter_Weight[i]) * 1000.0*Dilution_Factor/SampleVolume[i];
       
    }
    return out;
}
QVector<double> SampleData::VSS() const
{
    QVector<double> out(After_550_filtrate.size());
    for (int i = 0; i < out.size(); i++)
    {
        out[i] = (After_103_filtrate[i] - After_550_filtrate[i]) / SampleVolume[i] *1000000.0;

    }
    return out;
}

QVector<double> SampleData::TS() const
{
    QVector<double> out(Foil_Tray.size());
    for (int i = 0; i < out.size(); i++)
    {
        out[i] = (After_103_cake[i] - Foil_Tray[i])*100 / (Tray_plus_Sample[i]-Foil_Tray[i]);

    }
    return out;
}

QVector<double> SampleData::VS() const
{
    QVector<double> out(std::min(After_103_cake.size(),After_550_cake.size()));
    for (int i = 0; i < out.size(); i++)
    {
        out[i] = (After_103_cake[i] - After_550_cake[i]) / Tray_plus_Sample[i]*100 ;

    }
    return out;
}


double SampleData::TS_Avg() const
{
    return Average(TS());
}

double SampleData::VS_Avg() const
{
    return Average(VS());
}

double SampleData::Actual_Polymer_Added() const
{
    return Polymer_Before - Polymer_After;
}


double SampleData::Actual_Polymer_Added_lb_per_Ton() const
{
    return Actual_Polymer_Added()*parent->PolymerSolution *parent->grtolb/(Sludge_Weight*parent->grtoton*Actual_Belt_Filter_Press_before_PD_TS());
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
    json["Actual_Belt_Filter_Press_before_PD_TS"] = Actual_Belt_Filter_Press_before_PD_TS();
    json["Actual Polymer Added lb per Ton"] = Actual_Polymer_Added_lb_per_Ton(); 

    // Convert QVector<double> to QJsonArray using the helper function
    json["FoilTray_plus_Filter_Weight"] = vectorToJsonArray(FoilTray_plus_Filter_Weight);
    json["CST_Sludge"] = vectorToJsonArray(CST_Sludge);
    json["CST_Supernatant"] = vectorToJsonArray(CST_Supernatant);
    json["After_103_cake"] = vectorToJsonArray(After_103_cake);
    json["After_103_filtrate"] = vectorToJsonArray(After_103_filtrate);
    json["After_550_cake"] = vectorToJsonArray(After_550_cake);
    json["After_550_filtrate"] = vectorToJsonArray(After_550_filtrate);
    json["Foil_Tray"] = vectorToJsonArray(Foil_Tray);

	// Convert cacluated values to QJsonArray
	json["Calculated_polymer_added"] = Calculated_Polymer_Added();
	json["Actual_polymer_added"] = Actual_Polymer_Added();
	json["TS_percent"] = vectorToJsonArray(TS_percent());
	json["TSS"] = vectorToJsonArray(TSS());
	json["VSS"] = vectorToJsonArray(VSS());
	json["TSS (Avg)"] = TSS_Avg();
	json["VSS (Avg)"] = VSS_Avg();
	json["Actual_Belt_Filter_Press_before_PD_TS"] = Actual_Belt_Filter_Press_before_PD_TS();
    json["Filtered_Solids"] = Filtered_Solids();
    json["Flitrate"] = Filtrate();
	json["Estimated TS percent of Wet Solids on fabric"] = Estimated_TSp_of_Wet_Solids_on_frabic();
	json["TargetWSinCup"] = TargetWSinCup();
    json["CST Sludge (Avg)"] = CST_Sludge_Avg(); 
	json["CST Supernatant (Avg)"] = CST_Supernatant_Avg();
	json["SampleVolume"] = vectorToJsonArray(SampleVolume);
	json["TS"] = vectorToJsonArray(TS());
	json["TS(Avg)"] = TS_Avg();
    json["VS"] = vectorToJsonArray(VS());
    json["VS(Avg)"] = VS_Avg();
	json["Lab Filtrate TSS (mg TSS/L)"] = Lab_Filtrate_TSS();

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

QMap<QString, QVector<double>> SampleData::VariablesToMap() // Parnia: Shows variable in the table
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
    

    // Convert QVector<double> to Table Data
    out["FoilTray_plus_Filter_Weight"] = FoilTray_plus_Filter_Weight;
    out["CST_Sludge"] = CST_Sludge;
    out["CST_Supernatant"] = CST_Supernatant;
    out["After_103_cake"] = After_103_cake;
    out["After_103_filtrate"] = After_103_filtrate;
    out["After_550_cake"] = After_550_cake;
    out["After_550_filtrate"] = After_550_filtrate;
    out["Foil_Tray"] = Foil_Tray;

	// Convert cacluated values to Table Data
    out["Calculated_polymer_added"].append(Calculated_Polymer_Added());
    out["Actual_polymer_added"].append(Actual_Polymer_Added());
	out["Actual_polymer_added_lb_per_Ton"].append(Actual_Polymer_Added_lb_per_Ton());
    out["TS_percent"] = TS_percent();
    out["TSS"] = TSS();
    out["VSS"] = VSS();
    out["TSS (Avg)"].append(TSS_Avg());
    out["VSS (Avg)"].append(VSS_Avg());
    out["Actual_Belt_Filter_Press_before_PD_TS"].append(Actual_Belt_Filter_Press_before_PD_TS());
    out["Filtered_Solids"].append(Filtered_Solids());
    out["Filtrate"].append(Filtrate());
    out["Estimated_TS percent of Wet Solids on frabic"].append(Estimated_TSp_of_Wet_Solids_on_frabic());
	out["TargetWSinCup"].append(TargetWSinCup());
    out["CST Sludge (Avg)"].append(CST_Sludge_Avg());
	out["CST Supernatant (Avg)"].append(CST_Supernatant_Avg());
	out["SampleVolume"] = SampleVolume;
	out["TS"] = TS();
	out["TS(Avg)"].append(TS_Avg());
	out["VS"] = VS();
	out["VS(Avg)"].append(VS_Avg());
    out["Lab Filtrate TSS (mg TSS/L)"].append(Lab_Filtrate_TSS());
        
    return out;
}

double SampleData::TSS_Avg() const
{
    return Average(TSS());
}
double SampleData::VSS_Avg() const
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

unsigned int minsize(const QVector<double>& vec1, const QVector<double>& vec2, const QVector<double>& vec3)
{
	return std::min({ vec1.size(), vec2.size(), vec3.size() });

}

unsigned int minsize(const QVector<double>& vec1, const QVector<double>& vec2)
{
    return std::min({ vec1.size(), vec2.size()});

}

double SampleData::Filtered_Solids() const
{
    return Sieve_plus_Wet_Solids_Weight - Sieve_Weight;
}
double SampleData::Filtrate() const
{
    return Bucket_Filtrate - Bucket_Weight;
}

double SampleData::Estimated_TSp_of_Wet_Solids_on_frabic() const
{
    double term1 = (Filtered_Solids() + Filtrate()) / Filtered_Solids();
    double term2 = Sludge_Weight / (Sludge_Weight + Actual_Polymer_Added());
    return term1 * term2 * Actual_Belt_Filter_Press_before_PD_TS(); 
}

double SampleData::TargetWSinCup() const
{
    return parent->CupLoading()/Estimated_TSp_of_Wet_Solids_on_frabic()*100; 
}

double SampleData::CST_Sludge_Avg() const
{
    return Average(CST_Sludge);
}

double SampleData::CST_Supernatant_Avg() const
{
    return Average(CST_Supernatant);
}

double SampleData::Lab_Filtrate_TSS() const
{
    return TSS_Avg() * 1000; 
}