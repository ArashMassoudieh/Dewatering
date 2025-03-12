#include "TableModel.h"

TableModel::TableModel(const QMap<QString, QVector<double>>& data, QObject* parent)
    : QAbstractTableModel(parent), m_data(data) {
    m_keys = m_data.keys().toVector();  // Store keys for ordered row access
    calculateMaxColumns();              // Determine the number of columns
}

void TableModel::calculateMaxColumns() {
    m_maxColumns = 1;  // Start with 1 for the key column
    for (const auto& vec : m_data) {
        if (vec.size() > m_maxColumns) {
            m_maxColumns = vec.size();
        }
    }
}

int TableModel::rowCount(const QModelIndex& parent) const {
    return parent.isValid() ? 0 : m_data.size();
}

int TableModel::columnCount(const QModelIndex& parent) const {
    return parent.isValid() ? 0 : m_maxColumns;
}

QVariant TableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    int row = index.row();
    int col = index.column();

    if (row >= m_keys.size())
        return QVariant();

    const QString& key = m_keys[row];
    
    int valueIndex = col;
    if (valueIndex < m_data[key].size()) {
        return m_data[key][valueIndex];  // Return the value from QVector<double>
    }

    return QVariant();  // Empty cell for missing values
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        return QString("Value %1").arg(section+1);
    }
    else {
        return m_data.keys()[section];
    }
}

