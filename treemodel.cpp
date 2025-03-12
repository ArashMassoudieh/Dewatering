#include "treemodel.h"
#include "datasetcollection.h"
#include <QStringList>

using namespace Qt::StringLiterals;



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
    else
    {
        return Data->keys().at(index.row());
    }

}



Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    return index.isValid()
    ? QAbstractItemModel::flags(index) : Qt::ItemFlags(Qt::NoItemFlags);
}



QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    return "Experiment";
}



QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() || column != 0 || row >= Data->size())
        return QModelIndex();
    return createIndex(row, column);

}



QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}


int TreeModel::rowCount(const QModelIndex &parent) const
{
    return Data->count();
}



