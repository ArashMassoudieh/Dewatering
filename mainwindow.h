#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "BTC.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	const QString resource_directory = "/resources/"; 
    QMap<QString, CTimeSeries<double>*> graphsClipboard = QMap<QString, CTimeSeries<double>*>();
private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
