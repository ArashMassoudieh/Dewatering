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
        for (int j = 0; j < 5; j++)
        {
            if (xlsdoc->read(41 + i, 4 + j).isValid())
            {
                datapoint.CST_Sludge.append(xlsdoc->read(41 + i, 4 + j).toDouble());
            }
        }
        for (int j = 0; j < 5; j++)
        {
            if (xlsdoc->read(41 + i, 9 + j).isValid())
            {
                datapoint.CST_Supernatant.append(xlsdoc->read(41 + i, 9 + j).toDouble());
            }
        }

        //Foil Tray + Filter Weight
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(51 + i, 2 + j).isValid())
            {
                datapoint.FoilTray_plus_Filter_Weight.append(xlsdoc->read(51 + i, 2 + j).toDouble());
            }
        }
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(76 + i, 2 + j).isValid())
            {
                datapoint.FoilTray_plus_Filter_Weight.append(xlsdoc->read(76 + i, 2 + j).toDouble());
            }
        }


        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(62 + i, 4 + j).isValid())
            {
                datapoint.Tray_plus_Sample.append(xlsdoc->read(62 + i, 4 + j).toDouble());
            }
        }
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(84 + i, 4 + j).isValid())
            {
                datapoint.Tray_plus_Sample.append(xlsdoc->read(84 + i, 4 + j).toDouble());
            }
        }
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(51 + i, 4 + j).isValid())
            {
                datapoint.Sample_Volume.append(xlsdoc->read(51 + i, 4 + j).toDouble());
            }
        }
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(76 + i, 4 + j).isValid())
            {
                datapoint.Sample_Volume.append(xlsdoc->read(76 + i, 4 + j).toDouble());
            }
        }
        
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(51 + i, 6 + j).isValid())
            {
                datapoint.After_103_filtrate.append(xlsdoc->read(51 + i, 6 + j).toDouble());
            }
        }
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(76 + i, 6 + j).isValid())
            {
                datapoint.After_103_filtrate.append(xlsdoc->read(51 + i, 6 + j).toDouble());
            }
        }
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(51 + i, 12 + j).isValid())
            {
                datapoint.After_550_filtrate.append(xlsdoc->read(51 + i, 12 + j).toDouble());
          
            }
        }
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(76 + i, 12 + j).isValid())
            {
                datapoint.After_550_filtrate.append(xlsdoc->read(76 + i, 12 + j).toDouble());
            }
        }
        //Foil Tray (cake)
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(62 + i, 2 + j).isValid())
            {
                datapoint.Foil_Tray.append(xlsdoc->read(62 + i, 2 + j).toDouble());
            }
        }
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(85 + i, 2 + j).isValid())
            {
                datapoint.Foil_Tray.append(xlsdoc->read(85 + i, 2 + j).toDouble());
            }
        }
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(62 + i, 6 + j).isValid())
            {
                datapoint.After_103_cake.append(xlsdoc->read(62 + i, 6 + j).toDouble());
            }
        }
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(85 + i, 6 + j).isValid())
            {
                datapoint.After_103_cake.append(xlsdoc->read(85 + i, 6 + j).toDouble());
            }
        }
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(62 + i, 11 + j).isValid())
            {
                datapoint.After_550_cake.append(xlsdoc->read(62 + i, 11 + j).toDouble());
            }
        }
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(85 + i, 11 + j).isValid())
            {
                datapoint.After_550_cake.append(xlsdoc->read(85 + i, 11 + j).toDouble());
            }
        }
        // continue with all data

        // continue with all data

        Append(datapoint);
    }
    
    // Testing functions
    for (int i = 0; i < size(); i++)
    {
        qDebug() << at(i).TS_percent(); 
    }
    
    return true;
    // Testing functions
        for (int i = 0; i < size(); i++)
        {
            qDebug() << at(i).TSS();
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