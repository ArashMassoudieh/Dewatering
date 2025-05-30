#ifndef DATASETCOLLECTION_H
#define DATASETCOLLECTION_H

#include "DataSet.h"
#include "BTC.h"

struct parameters
{
    double CST_threshold; 
	double TSS_gradient_threshold;

};

class DataSetCollection : public QMap<QDate,DataSet>
{
public:
    DataSetCollection():QMap<QDate,DataSet>(){}
    DataSetCollection(const DataSetCollection &RHS):QMap<QDate,DataSet>(RHS){
		CalculationParameters = RHS.CalculationParameters;

    }
    DataSetCollection& operator=(const DataSetCollection &RHS)
    {
		if (this == &RHS) return *this; // self-assignment check
		CalculationParameters = RHS.CalculationParameters;
        QMap<QDate,DataSet>::operator=(RHS);
        return *this;
    }
    bool OpenExcel(const QString &filename);
    DataSetCollection(const QString &filename)
    {
        OpenExcel(filename);
    }

    QJsonObject toJson() const;
    bool SavetoJsonDocument(const QString &fileName) const;
    void SetCSTThreshold(double threshold) { CalculationParameters.CST_threshold = threshold; }
	void SetTSSGradientThreshold(double threshold) { CalculationParameters.TSS_gradient_threshold = threshold; }
    bool ExportToExcel(const QString& filePath) const;
	double GetCSTThreshold() const { return CalculationParameters.CST_threshold; }
	double GetTSSGradientThreshold() const { return CalculationParameters.TSS_gradient_threshold; }
    CTimeSeries<double> GetOPDTimeSeries() const;
    void SetErrorList(ErrorList* errorList) { errors = errorList; }
    ErrorList* GetErrorList() const { return errors; }
private:
	parameters CalculationParameters;
	ErrorList* errors = nullptr; // Pointer to an ErrorList for error handling


};

double toExcelDate(const QDate& date);
#endif // DATASETCOLLECTION_H
