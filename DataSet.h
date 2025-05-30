#pragma once

#include <qmap.h>
#include <QDate>
#include "SampleData.h"
#include "xlsxdocument.h"

class ErrorList;

enum RowNumbers
{
    
    CalculationStart = 33,
    CSTStart = 42,
    TSSVSSStart = 51,
    TSVSStart = 62,
    FinalCalculationStart = 72

};

class DataSetCollection; 

class DataSet: public QVector<SampleData>
{
public:
    // Variables
    QTime Sampling_time;
	QDate Sampling_date;
    QString Belt_No;
    double Poly_Ratio;
    double Sludge_Flow;
    double SBT3_TS_percent_LAB_TSPCT_J04;
    double BFPTS_percent; 
    double DIG_SLDG_FLOW_FROM_SBT;
    double DIL_WTR_FLOW_TO_BFP;
    double grtoton; 
    double grtolb = 0.002204623;
    double PolymerSolution; 
    double CupLoading() const {
        return CupArea() * 800;
    };
    double CupDiameter; 
    double CupArea() const { return 3.1415 * pow(CupDiameter* 0.0254, 2) / 4.0; }
    QPair<double,double> OPD() const;
    QPair<double, double> OPD_Haydees_formula() const;

    QMap<QString, QString> VariablesToMap() const;

    QPair<double,double>  ED() const; 
    // Default Constructor
    DataSet(DataSetCollection *_parent = nullptr) : QVector<SampleData>(),
        Poly_Ratio(0.0), Sludge_Flow(0.0), 
        SBT3_TS_percent_LAB_TSPCT_J04(0.0), DIG_SLDG_FLOW_FROM_SBT(0.0),
        DIL_WTR_FLOW_TO_BFP(0.0), BFPTS_percent(0.0), grtoton(0.0), grtolb(0.00220462262184878), PolymerSolution(0.0), CupDiameter(0.0) {
		parent = _parent; // Initialize the parent pointer
    }

	void SetParent(DataSetCollection* _parent) {
		parent = _parent; // Set the parent pointer
	}

    // Copy Constructor
    DataSet(const DataSet& other) : QVector<SampleData>(other),
        Sampling_time(other.Sampling_time),
		Sampling_date(other.Sampling_date),
        Belt_No(other.Belt_No),
        Poly_Ratio(other.Poly_Ratio),
        Sludge_Flow(other.Sludge_Flow),
        SBT3_TS_percent_LAB_TSPCT_J04(other.SBT3_TS_percent_LAB_TSPCT_J04),
        DIG_SLDG_FLOW_FROM_SBT(other.DIG_SLDG_FLOW_FROM_SBT),
        BFPTS_percent(other.BFPTS_percent),
        DIL_WTR_FLOW_TO_BFP(other.DIL_WTR_FLOW_TO_BFP),
        grtolb(other.grtolb),
        grtoton(other.grtoton),
		PolymerSolution(other.PolymerSolution),  // Initialize the new member variable
		CupDiameter(other.CupDiameter) // Initialize the new member variable
        {
		    for (int i = 0; i < other.size(); i++) {
			    SampleData sample = other.at(i);
			    sample.setParent(this); // Set the parent for each SampleData
				parent = other.parent; // Set the parent pointer
		}
    
    }

	// Assignment Operator
    DataSet& operator=(const DataSet& other) {
        if (this != &other) {
            QVector<SampleData>::operator=(other);
            Sampling_time = other.Sampling_time;
			Sampling_date = other.Sampling_date;
            Belt_No = other.Belt_No;
            Poly_Ratio = other.Poly_Ratio;
            Sludge_Flow = other.Sludge_Flow;
            SBT3_TS_percent_LAB_TSPCT_J04 = other.SBT3_TS_percent_LAB_TSPCT_J04;
            BFPTS_percent = other.BFPTS_percent; 
            DIG_SLDG_FLOW_FROM_SBT = other.DIG_SLDG_FLOW_FROM_SBT;
            DIL_WTR_FLOW_TO_BFP = other.DIL_WTR_FLOW_TO_BFP;
            grtoton = other.grtoton;
            grtolb = other.grtolb;
			PolymerSolution = other.PolymerSolution; // Assign the new member variable
			CupDiameter = other.CupDiameter; // Assign the new member variable
            for (SampleData& sample : *this) {
                sample.setParent(this);

                parent = other.parent; // Set the parent pointer
            }

        }
        
        return *this;
    }

    QVector<double> ExtractVariable(const QString& name) const;
    
    void Append(const SampleData& data)
    {
        append(data);
        last().setParent(this); 
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

    QString CreateAndFillSheet(QXlsx::Document& doc, const QString& sheetName) const;
	void SetErrorList(ErrorList* errorList) { errors = errorList; }
	ErrorList* GetErrorList() const { return errors; }
    unsigned int MaxSize(const QString& variableName) const;
private:
	DataSetCollection* parent = nullptr; // Pointer to the parent DataCollectionSet
	ErrorList* errors = nullptr; // Pointer to ErrorList for error handling

};

void writeHeaders(QXlsx::Document& doc, int& col, const QVector<QString>& headers);
void writeIndexedHeaders(QXlsx::Document& doc, int& col, const QString& base, int count);

template <typename T>
void writeVector(QXlsx::Document& doc, int row, int& col, const QVector<T>& vec, int maxSize);
QPair<double, double> interpolateXforY(const QVector<double>& xvalues, const QVector<double>& yvalues, double a);