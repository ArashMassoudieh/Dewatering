#include "datasetcollection.h"
#include <QJsonDocument>
#include <QFile>
#include <QIODevice>
#include <BTC.h>

bool DataSetCollection::OpenExcel(const QString &filename)
{
    if (!filename.isEmpty()) {
        qDebug() << "Selected file:" << filename;
    }
    else {
        qDebug() << "No file selected.";
        return false;
    }

    QXlsx::Document xlsx(filename);
    QStringList sheets = xlsx.sheetNames();
    qDebug()<<sheets;

    for (int i=0; i<sheets.size(); i++)
    {
        DataSet dataset(this);
        dataset.ReadSheet(&xlsx,sheets[i]);
        qDebug() << sheets[i];
        QStringList MDY = sheets[i].split("_");
        int month = MDY[0].toInt();
        int day = MDY[1].toInt();
        int year = MDY[2].toInt(); 
        QDate date = QDate(year, month, day);
        if (date.isValid())
            operator[](date) = dataset;

    }

    return true;
}

QJsonObject DataSetCollection::toJson() const
{
    QJsonObject out;
    for (QMap<QDate,DataSet>::const_iterator it = constBegin(); it!=constEnd(); it++ )
    {
        out[it.key().toString("MM_dd_yyyy")] = it.value().toJson();
    }
    return out;
}

bool DataSetCollection::SavetoJsonDocument(const QString &fileName) const
{
    QJsonDocument jsonDoc(toJson());
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error: Could not open file for writing:" << file.errorString();
        return false;
    }

    // Write JSON to file with indentation
    file.write(jsonDoc.toJson(QJsonDocument::Indented));
    file.close();

    qDebug() << "JSON saved successfully to" << fileName;
    return true;
}

bool  DataSetCollection::ExportToExcel(const QString& filePath) const
{
    QXlsx::Document xlsx;
    for (QMap<QDate, DataSet>::const_iterator it = constBegin(); it != constEnd(); it++)
    {
        QString sheetName = it.key().toString("MM_dd_yyyy");
        xlsx.addSheet(sheetName);
        xlsx.selectSheet(sheetName);
        it.value().CreateAndFillSheet(xlsx, sheetName);
    }
    return xlsx.saveAs(filePath);
    
}

CTimeSeries<double> DataSetCollection::GetOPDTimeSeries() const {
    CTimeSeries<double> ts;
    for (auto it = this->constBegin(); it != this->constEnd(); ++it) {
        QDate date = it.key();
        const DataSet& dataset = it.value();
        QPair<double, double> opd = dataset.OPD();
        ts.append(toExcelDate(date), opd.first);
    }
    return ts;
}

double toExcelDate(const QDate& date)
{
    // Excel epoch starts at 1899-12-31
    static const QDate excelEpoch(1899, 12, 31);

    if (!date.isValid() || date < excelEpoch)
        return std::numeric_limits<double>::quiet_NaN();  // invalid date

    int days = excelEpoch.daysTo(date);

    // Adjust for Excel leap year bug (dates >= 1900-03-01)
    if (date > QDate(1900, 2, 28))
        days += 1;

    return static_cast<double>(days);
}