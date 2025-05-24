#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts>
#include <QtWidgets/QRubberBand>

QT_USE_NAMESPACE


class SludgeAnalyzer;
class QPlotWindow;

class ChartView : public QChartView

{
public:
    ChartView(QChart *chart, QPlotWindow *plotWindow, SludgeAnalyzer *parent);
    QPlotWindow* PlotWindow() {return plotWindow;}
    void SetYLogAxis(bool val);
    bool Ylog() {return logYAxis;}

protected:
    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent( QMouseEvent * e );

private:
    bool m_isTouching;
    QPointF m_lastMousePos;
    bool double_clicked = false;
    SludgeAnalyzer *parent;
    QPlotWindow *plotWindow;
    bool logYAxis = false;
};

#endif
