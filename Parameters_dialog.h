#pragma once
#include <QDialog.h>
#include "ui_Parameters.h"

class DataSetCollection;


class Parameters_dialog : public QDialog
    
{
	Q_OBJECT

public:
	explicit Parameters_dialog(QWidget* parent = nullptr);

private:
	Ui:: Dialog ui;
	DataSetCollection* data = nullptr;
private slots:
	void onAccepted();
	void onRejected();
	void OnFileRequested();
};

