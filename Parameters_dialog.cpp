#include "Parameters_dialog.h"
#include "SludgeAnalyzer.h"
#include <QFileDialog>
#include <QDir>
#include <datasetcollection.h>
#include "ErrorList.h"
#include "ErrorListModel.h"

Parameters_dialog::Parameters_dialog(QWidget* parent)
{
	ui.setupUi(this);
	connect(ui.pushButtonExcelFileName, &QPushButton::clicked, this, &Parameters_dialog::OnFileRequested);
	connect(ui.okButton, &QPushButton::clicked, this, &Parameters_dialog::onAccepted);
	connect(ui.cancelButton, &QPushButton::clicked, this, &Parameters_dialog::onRejected);
    
}

void Parameters_dialog::onRejected()
{
	if (data) {
		delete data; // Clean up the data if it was allocated
		data = nullptr;
	}
	this->close(); // Close the dialog

}

void Parameters_dialog::OnFileRequested()
{
    QString filePath = QFileDialog::getOpenFileName(
        nullptr,
        "Open File",
        QDir::homePath(),
        "Text Files (*.xlsx);;All Files (*)"
    );

	ui.pushButtonExcelFileName->setText(filePath);
    data = new DataSetCollection();
    ErrorList* errors = new ErrorList();
    data->SetErrorList(errors);
    if (!filePath.isEmpty() && data->OpenExcel(filePath)) {
        qDebug() << "Selected file:" << filePath;
        data->SavetoJsonDocument("AllData.json");
        ErrorDialog dlg(errors);
        dlg.exec();
    }
    else {
        qDebug() << "Failed to open Excel file.";
        return;
    }
}

void Parameters_dialog::onAccepted()
{
	SludgeAnalyzer *w = new SludgeAnalyzer();
	w->SetData(data);
    w->SetThreshold(ui.lineEditCSTThreshold->text().toDouble(), ui.TSS_Deriv_Thresh->text().toDouble());
	w->show(); 

}
