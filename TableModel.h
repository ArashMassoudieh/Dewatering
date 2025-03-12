#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QMap>
#include <QString>
#include <QVector>


class TableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit TableModel(const QMap<QString, QVector<double>>& data, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QMap<QString, QVector<double>> m_data;
    QVector<QString> m_keys; // Ordered list of keys for row access
    int m_maxColumns;        // Largest QVector<double> size + 1

    void calculateMaxColumns();
};

#endif // TABLEMODEL_H


