#ifndef ERRORLISTMODEL_H
#define ERRORLISTMODEL_H

#include <QAbstractTableModel>
#include "ErrorList.h"
#include <QDialog>
#include <QTableView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>

class ErrorListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ErrorListModel(const ErrorList *errors, QObject* parent = nullptr)
        : QAbstractTableModel(parent) {
		m_errors = const_cast<ErrorList*>(errors);
        m_keys = m_errors->keys();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return m_errors->size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return 2;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();

        const QString& key = m_keys.at(index.row());
        return (index.column() == 0) ? key : m_errors->value(key);
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            return (section == 0) ? "Location" : "Error Description";
        }
        return QVariant();
    }

private:
    ErrorList *m_errors;
    QStringList m_keys;
};

class ErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorDialog(const ErrorList* errors, QWidget* parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle("Import Errors");
        resize(600, 400);

        auto* layout = new QVBoxLayout(this);
        auto* tableView = new QTableView(this);
        auto* model = new ErrorListModel(errors, this);
        tableView->setModel(model);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        auto* closeButton = new QPushButton("Close", this);
        connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);

        layout->addWidget(tableView);
        layout->addWidget(closeButton);
    }
};

#endif // ERRORLISTMODEL_H