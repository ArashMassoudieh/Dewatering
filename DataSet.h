#pragma once

#include <qmap.h>
#include <QDate>
#include "SampleData.h"
#include "xlsxdocument.h"


class DataSet: public QVector<SampleData>
{
public:
    // Variables
    QTime Sampling_time;
    QString Belt_No;
    double Poly_Ratio;
    double Sludge_Flow;
    double Polymer_sol;
    double SBT3_TS_percent_LAB_TSPCT_J04;
    double DIG_SLDG_FLOW_FROM_SBT;
    double DIL_WTR_FLOW_TO_BFP;

    // Default Constructor
    DataSet() : QVector<SampleData>(),
        Poly_Ratio(0.0), Sludge_Flow(0.0), Polymer_sol(0.0),
        SBT3_TS_percent_LAB_TSPCT_J04(0.0), DIG_SLDG_FLOW_FROM_SBT(0.0),
        DIL_WTR_FLOW_TO_BFP(0.0) {
    }

    // Copy Constructor
    DataSet(const DataSet& other) : QVector<SampleData>(other),
        Sampling_time(other.Sampling_time),
        Belt_No(other.Belt_No),
        Poly_Ratio(other.Poly_Ratio),
        Sludge_Flow(other.Sludge_Flow),
        Polymer_sol(other.Polymer_sol),
        SBT3_TS_percent_LAB_TSPCT_J04(other.SBT3_TS_percent_LAB_TSPCT_J04),
        DIG_SLDG_FLOW_FROM_SBT(other.DIG_SLDG_FLOW_FROM_SBT),
        DIL_WTR_FLOW_TO_BFP(other.DIL_WTR_FLOW_TO_BFP) {
    }

    // Assignment Operator
    DataSet& operator=(const DataSet& other) {
        if (this != &other) {
            QVector<SampleData>::operator=(other);
            Sampling_time = other.Sampling_time;
            Belt_No = other.Belt_No;
            Poly_Ratio = other.Poly_Ratio;
            Sludge_Flow = other.Sludge_Flow;
            Polymer_sol = other.Polymer_sol;
            SBT3_TS_percent_LAB_TSPCT_J04 = other.SBT3_TS_percent_LAB_TSPCT_J04;
            DIG_SLDG_FLOW_FROM_SBT = other.DIG_SLDG_FLOW_FROM_SBT;
            DIL_WTR_FLOW_TO_BFP = other.DIL_WTR_FLOW_TO_BFP;
        }
        return *this;
    }
    void Append(const SampleData& data)
    {
        append(data);
        last().parent = this; 
    }

    SampleData* getLast() {
        return &last();
    }
    // Destructor (optional, relies on QMap's default behavior)
    ~DataSet() {}

    //Utility functions
    bool ReadSheet(QXlsx::Document *xlsdoc, const QString &sheetname);
    QJsonObject toJson() const;

    int LookupSampleNumber(const QString& sample_number);


};

