#ifndef QPLOTWINDOW_H
#define QPLOTWINDOW_H

#include <QDialog>
#include <BTC.h>
#include <BTCSet.h>
#include <qplotter.h>

#define outputtimeseriesprecision double

class SludgeAnalyzer;
class ChartView;


namespace Ui {
class QPlotWindow;
}

class QPlotWindow : public QDialog
{
    Q_OBJECT

public:
    explicit QPlotWindow(SludgeAnalyzer *parent = nullptr);
    ~QPlotWindow();
    bool PlotData(const CTimeSeries<outputtimeseriesprecision>& BTC, bool allowtime=true, string style="line");
    bool PlotData(const CTimeSeriesSet<outputtimeseriesprecision>& BTC, bool allowtime=true, string style="line");
    bool AddData(const CTimeSeries<outputtimeseriesprecision>& BTC,bool allowtime=true, string style="line");
    void SetYAxisTitle(const QString& s)
    {
        y_Axis_Title = s;
        if (axisY)
            axisY->setTitleText(s);
    }
    void SetXAxisTitle(const QString& s)
    {
        x_Axis_Title = s;
        if (axisX_date)
            axisX_date->setTitleText(s);
        if (axisX_normal)
            axisX_normal->setTitleText(s);
    }
    void SetLegend(bool val);
    void SetTimeFormat(bool timedate);
    CTimeSeries<double> GetTimeSeries(const QString &name) {return TimeSeries[name];}
    bool SetYAxis(bool log);
private:
    Ui::QPlotWindow *ui;
    QPlotter* chart = nullptr;
    ChartView *chartview = nullptr;
    double xtoTime(const double &x) {
        return x * 86400 - 2209161600;

    }
    double timetoX(const double &time) {
        return (time + 2209161600) / 86400;
    }
    QDateTime xToDateTime(const double &xltime)
    {
        QDateTime temp_time = QDateTime::fromSecsSinceEpoch(xtoTime(xltime));
        int local_offset = temp_time.offsetFromUtc();
        int fixed_timestamp = xtoTime(xltime) - local_offset;
        QDateTime out = QDateTime::fromSecsSinceEpoch(fixed_timestamp);
        return out;

    }
    QMap<QString,CTimeSeries<double>> TimeSeries;
    QValueAxis* axisY = nullptr;
    QLogValueAxis* axisY_log = nullptr;
    QValueAxis* axisX_normal = nullptr;
    QDateTimeAxis *axisX_date = nullptr;
    double x_min_val = 1e7;
    double x_max_val = -1e7;
    double y_min_val = 1e7;
    double y_max_val = -1e7;
    QDateTime start;
    QDateTime end;
    QString x_Axis_Title;
    QString y_Axis_Title;


private slots:
     void contextMenuRequest(QPoint pos);
     void ExportToPNG();
     void ExportToCSV();

};

#endif // QPLOTWINDOW_H
