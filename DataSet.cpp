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

QString DataSet::CreateAndFillSheet(QXlsx::Document& doc, const QString& sheetName) const
{
    doc.addSheet(sheetName);
    doc.selectSheet(sheetName);

	int column_counter = 1;
	doc.write(1, column_counter, "Sample Number"); column_counter++;
	doc.write(1, column_counter, "Polymer Dose"); column_counter++;
	doc.write(1, column_counter, "Sludge Weight"); column_counter++;
	doc.write(1, column_counter, "Polymer Before"); column_counter++;
	doc.write(1, column_counter, "Polymer After"); column_counter++;
	doc.write(1, column_counter, "Sieve Weight"); column_counter++;
	doc.write(1, column_counter, "Bucket Weight"); column_counter++;
	doc.write(1, column_counter, "Sieve + Wet Solids Weight"); column_counter++;
	doc.write(1, column_counter, "Bucket Filtrate"); column_counter++;
    doc.write(1, column_counter, "Capture Efficiency"); column_counter++;
	doc.write(1, column_counter, "Dilution Factor");    column_counter++;
	doc.write(1, column_counter, "Tolerance"); column_counter++;
	doc.write(1, column_counter, "Tolerance2"); column_counter++;

    // For vector variables do this: 
    for (int i = 0; i < MaxSize("CST_Sludge"); i++)
    {
        doc.write(1, column_counter, "CST Sludge #" + QString::number(i+1)); column_counter++;
    }

    // For functions that return an array do this: 
    for (int i = 0; i < MaxSize("TSS"); i++)
    {
        doc.write(1, column_counter, "TSS #" + QString::number(i + 1)); column_counter++;
    }

    // For functions that return a single scalar do this: 
    doc.write(1, column_counter, "TS"); column_counter++;


    unsigned int row = 2;
    for (const SampleData& sample : *this)
	{
        int column_counter = 1; 
        doc.write(row, column_counter, sample.Sample_Number); column_counter++;
		doc.write(row, column_counter, sample.Polymer_Dose); column_counter++;
		doc.write(row, column_counter, sample.Sludge_Weight); column_counter++;
		doc.write(row, column_counter, sample.Polymer_Before); column_counter++;
		doc.write(row, column_counter, sample.Polymer_After); column_counter++;
		doc.write(row, column_counter, sample.Sieve_Weight); column_counter++;
		doc.write(row, column_counter, sample.Bucket_Weight); column_counter++;
		doc.write(row, column_counter, sample.Sieve_plus_Wet_Solids_Weight); column_counter++;
		doc.write(row, column_counter, sample.Bucket_Filtrate); column_counter++;
		doc.write(row, column_counter, sample.Capture_Efficiency); column_counter++;
		doc.write(row, column_counter, sample.Dilution_Factor); column_counter++;
		doc.write(row, column_counter, sample.Tolerance); column_counter++;
		doc.write(row, column_counter, sample.Tolerance2); column_counter++;
        //write the rest of variables entered by user
        
        // For vector variables do this: 
		for (int i = 0; i < MaxSize("CST_Sludge"); i++)
		{
			if (i < sample.CST_Sludge.size())
                doc.write(row, column_counter, sample.CST_Sludge[i]); column_counter++;
		}
        
        // For functions which return arrays do this: 
        for (int i = 0; i < MaxSize("TSS"); i++)
        {
            QVector<double> TSS = sample.TSS(); 
            if (i < TSS.size())
                doc.write(row, column_counter, TSS[i]); column_counter++;
        }

        // for functions that return a single scalar value do this
        doc.write(row, column_counter, sample.TS()); column_counter++;

        row++; 
	}

    return sheetName;
}

unsigned int DataSet::MaxSize(const QString& variableName) const
{
    unsigned int maxSize = 0;

    for (const SampleData& data : *this) {
        int size = 0;

        if (variableName == "FoilTray_plus_Filter_Weight")
            size = data.FoilTray_plus_Filter_Weight.size();
        else if (variableName == "CST_Sludge")
            size = data.CST_Sludge.size();
        else if (variableName == "CST_Supernatant")
            size = data.CST_Supernatant.size();
        else if (variableName == "Sample_Volume")
            size = data.Sample_Volume.size();
        else if (variableName == "After_103_cake")
            size = data.After_103_cake.size();
        else if (variableName == "After_103_filtrate")
            size = data.After_103_filtrate.size();
        else if (variableName == "Tray_plus_Sample")
            size = data.Tray_plus_Sample.size();
        else if (variableName == "After_550_cake")
            size = data.After_550_cake.size();
        else if (variableName == "After_550_filtrate")
            size = data.After_550_filtrate.size();
        else if (variableName == "Foil_Tray")
            size = data.Foil_Tray.size();
        else if (variableName == "TS_percent")
            size = data.TS_percent().size();
        else if (variableName == "TSS")
            size = data.TSS().size();
        else if (variableName == "VSS")
            size = data.VSS().size();
        else
            qWarning() << "Unknown variable name:" << variableName;

        if (size > static_cast<int>(maxSize))
            maxSize = size;
    }

    return maxSize;
}