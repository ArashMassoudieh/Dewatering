#ifndef DATASETCOLLECTION_H
#define DATASETCOLLECTION_H

#include "DataSet.h"


class DataSetCollection : public QMap<QDate,SampleData>
{
public:
    DataSetCollection():QMap<QDate,SampleData>(){}
    DataSetCollection(const DataSetCollection &RHS):QMap<QDate,SampleData>(RHS){}
    DataSetCollection& operator=(const DataSetCollection &RHS)
    {
        QMap<QDate,SampleData>::operator=(RHS);
        return *this;
    }
    bool OpenExcel(const QString &filename);
    DataSetCollection(const QString &filename)
    {
        OpenExcel(filename);
    }



};

#endif // DATASETCOLLECTION_H
