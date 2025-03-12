#include "treemodel.h"
#include "datasetcollection.h"
#include <QStringList>

//using namespace Qt::StringLiterals;



TreeModel::TreeModel(DataSetCollection *data, QObject *parent)
    : QAbstractItemModel(parent)
{
    Data = data;
}



TreeModel::~TreeModel() = default;



int TreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}


QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();

        if (!index.parent().isValid()) // Root level
        {
            return Data->keys().at(index.row());  // Top-level keys
        }
        else // Child level
        {
            QString parentKey = Data->keys().at(index.parent().row()).toString();
            return Data->value(QDate::fromString(parentKey,"MM_dd_yyyy"))[index.row()].Sample_Number;  // Return child value
        }

}



Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}



QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    return "Experiment";
}



QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid())  // Root level
    {
        return createIndex(row, column, nullptr);  // Root level item
    }
    else  // Child level
    {
        return createIndex(row, column, parent.row());  // Pass parent's row as internal id
    }

}



QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    int parentRow = static_cast<int>(index.internalId());

    if (parentRow == -1)  // Root level
        return QModelIndex();

    return createIndex(parentRow, 0, nullptr);
}


int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) // Root level
    {
        return Data->keys().size();
    }
    else  // Child level
    {
        QDate parentKey = Data->keys().at(parent.row());
        return Data->values(parentKey).size();
    }
}



