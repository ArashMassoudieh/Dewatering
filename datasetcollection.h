#ifndef DATASETCOLLECTION_H
#define DATASETCOLLECTION_H

#include "DataSet.h"


class DataSetCollection : public QMap<QDate,DataSet>
{
public:
    DataSetCollection():QMap<QDate,DataSet>(){}
    DataSetCollection(const DataSetCollection &RHS):QMap<QDate,DataSet>(RHS){}
    DataSetCollection& operator=(const DataSetCollection &RHS)
    {
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


};

#endif // DATASETCOLLECTION_H
