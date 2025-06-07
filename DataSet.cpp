#include "DataSet.h"
#include "DataSetCollection.h"
#include <xlsxcell.h>
#include <xlsxcellformula.h>

bool DataSet::ReadSheet(QXlsx::Document *xlsdoc, const QString &sheetname)
{
    
    
    xlsdoc->selectSheet(sheetname);
    Belt_No = xlsdoc->read("B8").toString();
    Sludge_Flow = xlsdoc->read("B10").toDouble();
    qDebug() << xlsdoc->read("B13");
    QString BFPTS_percent_str = xlsdoc->read("B13").toString();
    if (BFPTS_percent_str.contains("="))
    {
        BFPTS_percent = xlsdoc->read(BFPTS_percent_str.remove("=")).toDouble();
    }
    else
        BFPTS_percent = xlsdoc->read("B13").toDouble();
    
	
    SampleData plant_cake; 
    for (int i = 0; i < 100; i++)
    {
        if (xlsdoc->read(i, 1).isValid())
        {
            if (xlsdoc->read(i, 1).toString().contains("Plant Cake"))
            {
                plant_cake.Sample_Number = xlsdoc->read(i, 1).toString();
                if (xlsdoc->read(i, 2).toDouble() != 0) plant_cake.Foil_Tray.append(xlsdoc->read(i, 2).toDouble());
                if (xlsdoc->read(i, 3).toDouble() != 0) plant_cake.Foil_Tray.append(xlsdoc->read(i, 3).toDouble());
                if (xlsdoc->read(i, 4).toDouble() != 0) plant_cake.Tray_plus_Sample.append(xlsdoc->read(i, 4).toDouble());
                if (xlsdoc->read(i, 5).toDouble() != 0) plant_cake.Tray_plus_Sample.append(xlsdoc->read(i, 5).toDouble());
                if (xlsdoc->read(i, 6).toDouble() != 0) plant_cake.After_103_cake.append(xlsdoc->read(i, 6).toDouble());
                if (xlsdoc->read(i, 7).toDouble() != 0) plant_cake.After_103_cake.append(xlsdoc->read(i, 7).toDouble());
                Append(plant_cake); // Append the plant cake data to the dataset
                break;
            }
            
        }
    }


    SampleData sludge;
    for (int i = 0; i < 100; i++)
    {
        if (xlsdoc->read(i, 1).isValid())
        {
			qDebug() << xlsdoc->read(i, 1).toString();
            if (xlsdoc->read(i, 1).toString()== "Sludge")
            {
                sludge.Sample_Number = xlsdoc->read(i, 1).toString();
                if (xlsdoc->read(i, 2).toDouble() != 0) sludge.Foil_Tray.append(xlsdoc->read(i, 2).toDouble());
                if (xlsdoc->read(i, 3).toDouble() != 0) sludge.Foil_Tray.append(xlsdoc->read(i, 3).toDouble());
                if (xlsdoc->read(i, 4).toDouble() != 0) sludge.Tray_plus_Sample.append(xlsdoc->read(i, 4).toDouble());
                if (xlsdoc->read(i, 5).toDouble() != 0) sludge.Tray_plus_Sample.append(xlsdoc->read(i, 5).toDouble());
                if (xlsdoc->read(i, 6).toDouble() != 0) sludge.After_103_cake.append(xlsdoc->read(i, 6).toDouble());
                if (xlsdoc->read(i, 7).toDouble() != 0) sludge.After_103_cake.append(xlsdoc->read(i, 7).toDouble());
                Append(sludge); // Append the plant cake data to the dataset
                break;
            }
           
        }
    }

    SampleData plant_filtrate;
    for (int i = 0; i < 100; i++)
    {
        if (xlsdoc->read(i, 1).isValid())
        {
            if (xlsdoc->read(i, 1).toString().contains("Plant Filterate"))
            {
                plant_filtrate.Sample_Number = xlsdoc->read(i, 1).toString();
                if (xlsdoc->read(i, 2).toDouble() != 0) plant_filtrate.FoilTray_plus_Filter_Weight.append(xlsdoc->read(i, 2).toDouble());
                if (xlsdoc->read(i, 3).toDouble() != 0) plant_filtrate.FoilTray_plus_Filter_Weight.append(xlsdoc->read(i, 3).toDouble());
                if (xlsdoc->read(i, 4).toDouble() != 0) plant_filtrate.After_103_filtrate.append(xlsdoc->read(i, 6).toDouble());
                if (xlsdoc->read(i, 5).toDouble() != 0) plant_filtrate.After_103_filtrate.append(xlsdoc->read(i, 7).toDouble());
                Append(plant_filtrate); // Append the plant cake data to the dataset
                break;
            }
            
        }
    }

    double gr_to_lb = xlsdoc->read("B19").toDouble();
    if (gr_to_lb!=0.0)
        grtolb = gr_to_lb;
    grtoton = xlsdoc->read("B20").toDouble();
	PolymerSolution = xlsdoc->read("B27").toDouble();
	CupDiameter = xlsdoc->read("B21").toDouble();
    //Reading data related to samples
    for (int i = 0; i < 7; i++)
    {
        SampleData datapoint;
        datapoint.setParent(this); 
		if (errors)
		{
			datapoint.SetErrorList(errors); // Set the error list for each SampleData
		}
                
        datapoint.Sample_Number = xlsdoc->read(RowNumbers::TSVSStart+i,1).toString();
        datapoint.Polymer_Dose = xlsdoc->read(RowNumbers::CalculationStart + i, 2).toDouble();
        datapoint.Sludge_Weight = xlsdoc->read(RowNumbers::CalculationStart + i, 4).toDouble();
        datapoint.Polymer_Before = xlsdoc->read(RowNumbers::CalculationStart + i, 6).toDouble();
        datapoint.Polymer_After = xlsdoc->read(RowNumbers::CalculationStart + i, 7).toDouble();
        datapoint.Sieve_Weight = xlsdoc->read(RowNumbers::CalculationStart + i, 10).toDouble();
        datapoint.Bucket_Weight = xlsdoc->read(RowNumbers::CalculationStart + i, 11).toDouble();
        datapoint.Sieve_plus_Wet_Solids_Weight = xlsdoc->read(RowNumbers::CalculationStart + i, 12).toDouble();
        datapoint.Bucket_Filtrate = xlsdoc->read(RowNumbers::CalculationStart + i, 13).toDouble();
        datapoint.Capture_Efficiency = xlsdoc->read(RowNumbers::CalculationStart + i, 14).toDouble();
        datapoint.Dilution_Factor = xlsdoc->read(RowNumbers::CalculationStart + i, 15).toDouble();
        datapoint.Tolerance = xlsdoc->read(RowNumbers::CalculationStart + i, 16).toDouble();
        datapoint.Tolerance2 = xlsdoc->read(RowNumbers::CalculationStart + i, 17).toDouble();
              
        
        for (int j = 0; j < 5; j++)
        {
            if (xlsdoc->read(RowNumbers::CSTStart + i, 4 + j).isValid())
            {
                datapoint.CST_Sludge.append(xlsdoc->read(RowNumbers::CSTStart + i, 4 + j).toDouble());
            }
        }
        for (int j = 0; j < 5; j++)
        {
            if (xlsdoc->read(RowNumbers::CSTStart + i, 9 + j).isValid())
            {
                datapoint.CST_Supernatant.append(xlsdoc->read(RowNumbers::CSTStart + i, 9 + j).toDouble());
            }
        }

        //Foil Tray + Filter Weight
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(RowNumbers::TSSVSSStart + i, 2 + j).isValid())
            {
                datapoint.FoilTray_plus_Filter_Weight.append(xlsdoc->read(RowNumbers::TSSVSSStart + i, 2 + j).toDouble());
            }
        }
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(RowNumbers::TSSVSSStart + i, 4 + j).isValid())
            {
                datapoint.SampleVolume.append(xlsdoc->read(RowNumbers::TSSVSSStart + i, 4 + j).toDouble());
            }
        }

       /* for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(76 + i, 2 + j).isValid())
            {
                datapoint.FoilTray_plus_Filter_Weight.append(xlsdoc->read(76 + i, 2 + j).toDouble());
            }
        }*/


        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(62 + i, 4 + j).isValid())
            {
                datapoint.Tray_plus_Sample.append(xlsdoc->read(62 + i, 4 + j).toDouble());
            }
        }
       /* for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(84 + i, 4 + j).isValid())
            {
                datapoint.Tray_plus_Sample.append(xlsdoc->read(84 + i, 4 + j).toDouble());
            }
        }*/
      
        /*for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(76 + i, 4 + j).isValid())
            {
                datapoint.Sample_Volume.append(xlsdoc->read(76 + i, 4 + j).toDouble());
            }
        }*/
        
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(RowNumbers::TSSVSSStart + i, 6 + j).isValid())
            {
                datapoint.After_103_filtrate.append(xlsdoc->read(RowNumbers::TSSVSSStart + i, 6 + j).toDouble());
            }
        }
       
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(52 + i, 12 + j).isValid())
            {
                datapoint.After_550_filtrate.append(xlsdoc->read(RowNumbers::TSSVSSStart + i, 12 + j).toDouble());
          
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
            if (xlsdoc->read(62 + i, 6 + j).isValid())
            {
                datapoint.After_103_cake.append(xlsdoc->read(62 + i, 6 + j).toDouble());
            }
        }
       
        for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(62 + i, 11 + j).isValid())
            {
                datapoint.After_550_cake.append(xlsdoc->read(62 + i, 11 + j).toDouble());
            }
        }
        /*for (int j = 0; j < 2; j++)
        {
            if (xlsdoc->read(85 + i, 11 + j).isValid())
            {
                datapoint.After_550_cake.append(xlsdoc->read(85 + i, 11 + j).toDouble());
            }
        }*/

        if (xlsdoc->read(RowNumbers::TSSVSSStart + i, 8).isValid())
        {
            datapoint.Dilution_Factor = xlsdoc->read(50+i, 8).toDouble();
        }

        if (xlsdoc->read(RowNumbers::FinalCalculationStart + i, 8).isValid())
        {
            datapoint.Tolerance = xlsdoc->read(RowNumbers::FinalCalculationStart + i, 8).toDouble();
        }
        if (xlsdoc->read(RowNumbers::FinalCalculationStart + i, 20).isValid())
        {
            datapoint.Tolerance2 = xlsdoc->read(RowNumbers::FinalCalculationStart + i, 20).toDouble();
        }

        // continue with all data

        // continue with all data

        Append(datapoint);
		
    }
    
    
    if (BFPTS_percent == 0.0 && this->LookupSampleNumber("Sludge")!=-1)
    {
        BFPTS_percent = this->value(LookupSampleNumber("Sludge")).TS_Avg();
    }
    

    // Testing functions
    for (int i = 0; i < size(); i++)
    {
        qDebug() << at(i).TS_percent(); 
    }
    
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
	json["BFPTS_percent"] = BFPTS_percent;
    json["SBT3_TS_percent_LAB_TSPCT_J04"] = SBT3_TS_percent_LAB_TSPCT_J04;
    json["DIG_SLDG_FLOW_FROM_SBT"] = DIG_SLDG_FLOW_FROM_SBT;
    json["DIL_WTR_FLOW_TO_BFP"] = DIL_WTR_FLOW_TO_BFP;
	json["grtoton"] = grtoton;
	json["grtolb"] = grtolb;
	json["PolymerSolution"] = PolymerSolution;
	json["CupLoading"] = CupLoading();
    json["CupDiameter"] = CupDiameter;
    json["CupArea"] = CupArea(); 
    json["OPD"] = OPD().second;
	json["CST @ OPD"] = OPD().first;
    json["OPD_H"] = OPD_Haydees_formula().second;
    json["CST @ OPD_H"] = OPD_Haydees_formula().first;

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
        if (value(i).Sample_Number == sample_number)
            return i;

    }
    return -1; 
}

void writeHeaders(QXlsx::Document& doc, int& col, const QVector<QString>& headers) {
    for (const QString& header : headers)
        doc.write(1, col++, header);
}

// Helper to write indexed headers like "CST Sludge #1"
void writeIndexedHeaders(QXlsx::Document& doc, int& col, const QString& base, int count) {
    for (int i = 0; i < count; ++i)
        doc.write(1, col++, base + " #" + QString::number(i + 1));
}

// Helper to write vector data
template <typename T>
void writeVector(QXlsx::Document& doc, int row, int& col, const QVector<T>& vec, int maxSize) {
    for (int i = 0; i < maxSize; ++i)
        doc.write(row, col++, i < vec.size() ? QVariant(vec[i]) : QVariant());
}

QString DataSet::CreateAndFillSheet(QXlsx::Document& doc, const QString& sheetName) const {
    doc.addSheet(sheetName);
    doc.selectSheet(sheetName);

    int col = 1;
    writeHeaders(doc, col, {
        "Sample Number", "Polymer Dose", "Actual Belt Filter Press before PD TS", "Sludge Weight",
        "Calculated Polymer Added", "Polymer Before", "Polymer After", "Actual Polymer Added",
        "Actual Polymer Added (lb/ton)", "Sieve Weight", "Bucket Weight",
        "Sieve + Wet Solids Weight", "Bucket + Filtrate", "Capture Efficiency",
        "Filtered Solids", "Filtrate", "Estimated TS% of Wet Solids", "Target WS in Cup"
        });

    writeIndexedHeaders(doc, col, "CST Sludge", MaxSize("CST_Sludge"));
    doc.write(1, col++, "CST Sludge (Avg)");
    writeIndexedHeaders(doc, col, "CST Supernatant", MaxSize("CST_Supernatant"));
    doc.write(1, col++, "CST Supernatant (Avg)");
    writeIndexedHeaders(doc, col, "Foil Tray + Filter Weight", MaxSize("FoilTray_plus_Filter_Weight"));
    writeIndexedHeaders(doc, col, "Sample Volume", MaxSize("SampleVolume"));
    writeIndexedHeaders(doc, col, "After 103 filtrate", MaxSize("After_103_filtrate"));
    doc.write(1, col++, "Dilution Factor");
    writeIndexedHeaders(doc, col, "TSS", MaxSize("TSS"));
    doc.write(1, col++, "TSS (Avg)");
    writeIndexedHeaders(doc, col, "After 550 filtrate", MaxSize("After_550_filtrate"));
    writeIndexedHeaders(doc, col, "VSS", MaxSize("VSS"));
    doc.write(1, col++, "VSS (Avg)");
    writeIndexedHeaders(doc, col, "Foil Tray", MaxSize("Foil_Tray"));
    writeIndexedHeaders(doc, col, "Tray plus Sample", MaxSize("Tray_plus_Sample"));
    writeIndexedHeaders(doc, col, "After 103 cake", MaxSize("After_103_cake"));
    writeIndexedHeaders(doc, col, "TS", MaxSize("TS"));
    doc.write(1, col++, "TS (Avg)");
    writeIndexedHeaders(doc, col, "After 550 cake", MaxSize("After_550_cake"));
    writeIndexedHeaders(doc, col, "VS", MaxSize("VS"));
    doc.write(1, col++, "VS (Avg)");
    doc.write(1, col++, "Tolerance");
    doc.write(1, col++, "Tolerance2");

    int row = 2;
    for (const SampleData& sample : *this) {
        int col = 1;
        doc.write(row, col++, sample.Sample_Number);
        doc.write(row, col++, sample.Polymer_Dose);
        doc.write(row, col++, sample.Actual_Belt_Filter_Press_before_PD_TS());
        doc.write(row, col++, sample.Sludge_Weight);
        doc.write(row, col++, sample.Calculated_Polymer_Added());
        doc.write(row, col++, sample.Polymer_Before);
        doc.write(row, col++, sample.Polymer_After);
        doc.write(row, col++, sample.Actual_Polymer_Added());
        doc.write(row, col++, sample.Actual_Polymer_Added_lb_per_Ton());
        doc.write(row, col++, sample.Sieve_Weight);
        doc.write(row, col++, sample.Bucket_Weight);
        doc.write(row, col++, sample.Sieve_plus_Wet_Solids_Weight);
        doc.write(row, col++, sample.Bucket_Filtrate);
        doc.write(row, col++, sample.Capture_Efficiency);
        doc.write(row, col++, sample.Filtered_Solids());
        doc.write(row, col++, sample.Filtrate());
        doc.write(row, col++, sample.Estimated_TSp_of_Wet_Solids_on_frabic());
        doc.write(row, col++, sample.TargetWSinCup());

        writeVector(doc, row, col, sample.CST_Sludge, MaxSize("CST_Sludge"));
        doc.write(row, col++, sample.CST_Sludge_Avg());
        writeVector(doc, row, col, sample.CST_Supernatant, MaxSize("CST_Supernatant"));
        doc.write(row, col++, sample.CST_Supernatant_Avg());
        writeVector(doc, row, col, sample.FoilTray_plus_Filter_Weight, MaxSize("FoilTray_plus_Filter_Weight"));
        writeVector(doc, row, col, sample.SampleVolume, MaxSize("SampleVolume"));
        writeVector(doc, row, col, sample.After_103_filtrate, MaxSize("After_103_filtrate"));
        doc.write(row, col++, sample.Dilution_Factor);
        writeVector(doc, row, col, sample.TSS(), MaxSize("TSS"));
        doc.write(row, col++, sample.TSS_Avg());
        writeVector(doc, row, col, sample.After_550_filtrate, MaxSize("After_550_filtrate"));
        writeVector(doc, row, col, sample.VSS(), MaxSize("VSS"));
        doc.write(row, col++, sample.VSS_Avg());
        writeVector(doc, row, col, sample.Foil_Tray, MaxSize("Foil_Tray"));
        writeVector(doc, row, col, sample.Tray_plus_Sample, MaxSize("Tray_plus_Sample"));
        writeVector(doc, row, col, sample.After_103_cake, MaxSize("After_103_cake"));
        writeVector(doc, row, col, sample.TS(), MaxSize("TS"));
        doc.write(row, col++, sample.TS_Avg());
        writeVector(doc, row, col, sample.After_550_cake, MaxSize("After_550_cake"));
        writeVector(doc, row, col, sample.VS(), MaxSize("VS"));
        doc.write(row, col++, sample.VS_Avg());
        doc.write(row, col++, sample.Tolerance);
        doc.write(row, col++, sample.Tolerance2);

        ++row;
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
        else if (variableName == "SampleVolume")
            size = data.SampleVolume.size();
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
        else if (variableName == "TS")
            size = data.TS().size();
        else if (variableName == "VS")
            size = data.VS().size();
        else
            qWarning() << "Unknown variable name:" << variableName;

        if (size > static_cast<int>(maxSize))
            maxSize = size;
    }

    return maxSize;
}

QPair<double,double> DataSet::OPD() const
{
	QPair<double, double> result;
    QVector<double> xvalues = ExtractVariable("Actual_Polymer_Added_lb_per_Ton");
    QVector<double> yvalues = ExtractVariable("CST_Sludge_Avg");
	return interpolateXforY(xvalues, yvalues, parent->GetCSTThreshold() );
    
}

QPair<double, double> DataSet::OPD_Haydees_formula() const
{
    QPair<double, double> result;
    QVector<double> xvalues = ExtractVariable("Actual_Polymer_Added_lb_per_Ton");
    QVector<double> yvalues = ExtractVariable("CST_Sludge_Avg");
    QVector<double> MovingAverage;
	for (int i = 0; i < yvalues.size(); i++)
	{
		if (i < 1) {
			MovingAverage.append(yvalues[i]);
		}
		else {
			double avg = (yvalues[i] + yvalues[i - 1]) / 2.0;
			MovingAverage.append(avg);
		}
	}
	QVector<double> difference;
    for (int i = 1; i < yvalues.size(); i++)
    {
		double diff = (MovingAverage[i] - yvalues[i])*100/ MovingAverage[i];
		difference.append(diff);
    }
    for (int i = 1; i < difference.size(); i++)
    {
        if (difference[i - 1] > 10 && difference[i] < 10)
		{
			result.first = xvalues[i];
			result.second = yvalues[i];
            break;
		}
    }
    return result; 
}

QMap<QString, QString> DataSet::VariablesToMap() const
{
    QMap<QString, QString> out; 
	out["ED"] = QString::number(ED().first);
	out["ED_CST"] = QString::number(ED().second);
	out["OPD"] = QString::number(OPD().first);
	out["OPD_CST"] = QString::number(OPD().second);
	out["OPD_H"] = QString::number(OPD_Haydees_formula().first);
	out["OPD_H_CST"] = QString::number(OPD_Haydees_formula().second);
	out["PolymerSolution"] = QString::number(PolymerSolution);
	out["CupDiameter"] = QString::number(CupDiameter);
	out["CupArea"] = QString::number(CupArea());
	out["Belt_No"] = Belt_No;
	out["Sludge_Flow"] = QString::number(Sludge_Flow);
	out["Poly_Ratio"] = QString::number(Poly_Ratio);
	out["BFPTS_percent"] = QString::number(BFPTS_percent);
	out["SBT3_TS_percent_LAB_TSPCT_J04"] = QString::number(SBT3_TS_percent_LAB_TSPCT_J04);
	out["DIG_SLDG_FLOW_FROM_SBT"] = QString::number(DIG_SLDG_FLOW_FROM_SBT);
	out["DIL_WTR_FLOW_TO_BFP"] = QString::number(DIL_WTR_FLOW_TO_BFP);
	out["grtoton"] = QString::number(grtoton);
	out["grtolb"] = QString::number(grtolb);
	out["Sampling_time"] = Sampling_time.toString("hh:mm:ss");
	out["Sampling_date"] = Sampling_date.toString(Qt::ISODate);
    return out; 
}

QPair<double, double> DataSet::ED() const
{
    return QPair<double, double>();
}

QVector<double> DataSet::ExtractVariable(const QString& name) const {
    QVector<double> result;
    result.reserve(this->size());

    for (const SampleData& sample : *this) {
		if (sample.Sample_Number.toInt()==0)
			continue;  // Skip empty sample numbers
        if (name == "Sludge_Weight") result.append(sample.Sludge_Weight);
        else if (name == "Polymer_Dose") result.append(sample.Polymer_Dose);
        else if (name == "Polymer_Before") result.append(sample.Polymer_Before);
        else if (name == "Polymer_After") result.append(sample.Polymer_After);
        else if (name == "Sieve_Weight") result.append(sample.Sieve_Weight);
        else if (name == "Bucket_Weight") result.append(sample.Bucket_Weight);
        else if (name == "Sieve_plus_Wet_Solids_Weight") result.append(sample.Sieve_plus_Wet_Solids_Weight);
        else if (name == "Bucket_Filtrate") result.append(sample.Bucket_Filtrate);
        else if (name == "Capture_Efficiency") result.append(sample.Capture_Efficiency);
        else if (name == "Dilution_Factor") result.append(sample.Dilution_Factor);
        else if (name == "Tolerance") result.append(sample.Tolerance);
        else if (name == "Tolerance2") result.append(sample.Tolerance2);

        // Functions
        else if (name == "Calculated_Polymer_Added") result.append(sample.Calculated_Polymer_Added());
        else if (name == "Actual_Belt_Filter_Press_before_PD_TS") result.append(sample.Actual_Belt_Filter_Press_before_PD_TS());
        else if (name == "Actual_Polymer_Added") result.append(sample.Actual_Polymer_Added());
        else if (name == "Actual_Polymer_Added_lb_per_Ton") result.append(sample.Actual_Polymer_Added_lb_per_Ton());
        else if (name == "TSS_Avg") result.append(sample.TSS_Avg());
        else if (name == "VSS_Avg") result.append(sample.VSS_Avg());
        else if (name == "TS_Avg") result.append(sample.TS_Avg());
        else if (name == "VS_Avg") result.append(sample.VS_Avg());
        else if (name == "Filtered_Solids") result.append(sample.Filtered_Solids());
        else if (name == "Filtrate") result.append(sample.Filtrate());
        else if (name == "Estimated_TSp_of_Wet_Solids_on_frabic") result.append(sample.Estimated_TSp_of_Wet_Solids_on_frabic());
        else if (name == "TargetWSinCup") result.append(sample.TargetWSinCup());
        else if (name == "CST_Sludge_Avg") result.append(sample.CST_Sludge_Avg());
        else if (name == "CST_Supernatant_Avg") result.append(sample.CST_Supernatant_Avg());
        else if (name == "Lab_Filtrate_TSS") result.append(sample.Lab_Filtrate_TSS());

        else result.append(qQNaN());  // Unknown variable
    }

    return result;
}


QPair<double, double> interpolateXforY(
    const QVector<double>& xvalues,
    const QVector<double>& yvalues,
    double a)
{
    if (xvalues.size() != yvalues.size() || xvalues.size() < 2)
        return qMakePair(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN());

    // Compute target y-value
    double ymin = *std::min_element(yvalues.begin(), yvalues.end());
    double ymax = *std::max_element(yvalues.begin(), yvalues.end());
    double y_target = (ymax-ymin)*a + ymin;

    QPair<double, double> best_result = qMakePair(std::numeric_limits<double>::max(), std::numeric_limits<double>::quiet_NaN());

    for (int i = 0; i < yvalues.size() - 1; ++i)
    {
        double y1 = yvalues[i];
        double y2 = yvalues[i + 1];

        if ((y_target <= y1 && y_target >= y2) || (y_target >= y1 && y_target <= y2))
        {
            double t = (y_target - y1) / (y2 - y1);
            double x_interp = xvalues[i] + t * (xvalues[i + 1] - xvalues[i]);
            double y_interp = y1 + t * (y2 - y1);

            // Keep the one with the smallest x
            if (x_interp < best_result.first)
                best_result = qMakePair(x_interp, y_interp);
        }
    }

    if (best_result.first == std::numeric_limits<double>::max())
        return qMakePair(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN());

    return best_result;
}
