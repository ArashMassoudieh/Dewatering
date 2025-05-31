#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QMap>
#include <QString>
#include <type_traits>

template <typename T>
class TableModel : public QAbstractTableModel
{
public:
    explicit TableModel(const QMap<QString, T>& data, QObject* parent = nullptr)
        : QAbstractTableModel(parent), m_data(data)
    {
        m_keys = m_data.keys().toVector();
        calculateMaxColumns();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return parent.isValid() ? 0 : m_data.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return parent.isValid() ? 0 : m_maxColumns;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();

        const QString& key = m_keys[index.row()];
        const T& value = m_data[key];

        // Case: T is QVector<double>
        if constexpr (std::is_same_v<T, QVector<double>>) {
            if (index.column() < value.size())
                return value[index.column()];
            return QVariant();
        }
        // Case: T is QString
        else if constexpr (std::is_same_v<T, QString>) {
            return (index.column() == 0) ? value : QVariant();
        }
        // Fallback: Show nothing
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            if constexpr (std::is_same_v<T, QVector<double>>)
                return QString("Value %1").arg(section + 1);
            else
                return "Value";
        }
        else {
            return m_keys[section];
        }
    }

private:
    void calculateMaxColumns() {
        if constexpr (std::is_same_v<T, QVector<double>>) {
            m_maxColumns = 1;
            for (const auto& vec : m_data) {
                if (vec.size() > m_maxColumns)
                    m_maxColumns = vec.size();
            }
        }
        else {
            m_maxColumns = 1; // Only one column for non-vector types
        }
    }

    QMap<QString, T> m_data;
    QVector<QString> m_keys;
    int m_maxColumns = 1;
};

#endif // TABLEMODEL_H



