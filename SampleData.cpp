#include "SampleData.h"

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
