#include "DataSet.h"

bool DataSet::ReadSheet(QXlsx::Document *xlsdoc, const QString &sheetname)
{
    xlsdoc->selectSheet(sheetname);
    Belt_No = xlsdoc->read("B8").toString();
    Sludge_Flow = xlsdoc->read("B10").toDouble();

    //Reading data related to samples
    for (int i = 0; i < 6; i++)
    {
        SampleData datapoint;
        int j = xlsdoc->read(33+i, 1).toInt();
        datapoint.Sample_Number = QString::number(xlsdoc->read(33+i,1).toInt());
        datapoint.Polymer_Dose = xlsdoc->read(33 + i, 2).toDouble();
        datapoint.Sludge_Weight = xlsdoc->read(33 + i, 4).toDouble();
        datapoint.Polymer_Before = xlsdoc->read(33 + i, 6).toDouble();
        datapoint.Polymer_After = xlsdoc->read(33 + i, 7).toDouble();
        datapoint.Sieve_Weight = xlsdoc->read(33 + i, 10).toDouble();
        datapoint.Bucket_Weight = xlsdoc->read(33 + i, 11).toDouble();

        // continue with all data

        Append(datapoint);
    }
    return true;
}

// Function to convert to QJsonObject
QJsonObject DataSet::toJson() const {
    QJsonObject json;

    // Convert primitive data types
    json["Sampling_time"] = Sampling_time.toString("hh:mm:ss");
    json["Belt_No"] = Belt_No;
    json["Poly_Ratio"] = Poly_Ratio;
    json["Sludge_Flow"] = Sludge_Flow;
    json["Polymer_sol"] = Polymer_sol;
    json["SBT3_TS_percent_LAB_TSPCT_J04"] = SBT3_TS_percent_LAB_TSPCT_J04;
    json["DIG_SLDG_FLOW_FROM_SBT"] = DIG_SLDG_FLOW_FROM_SBT;
    json["DIL_WTR_FLOW_TO_BFP"] = DIL_WTR_FLOW_TO_BFP;

    // Convert QVector<SampleData> to QJsonArray
    QJsonArray samplesArray;
    for (const SampleData& sample : *this) {
        samplesArray.append(sample.toJson());
    }
    json["Samples"] = samplesArray;

    return json;
}

int DataSet::LookupSampleNumber(const QString& sample_number)
{
    for (int i = 0; i < size(); i++)
    {
        if (at(i).Sample_Number == sample_number)
            return i;

    }
    return -1; 
}