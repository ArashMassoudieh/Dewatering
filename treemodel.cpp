#include "TreeModel.h"

TreeModel::TreeModel(DataSetCollection *data, QObject* parent)
    : QAbstractItemModel(parent) {
    m_rootItem = new TreeItem(QVariant()); // Root item doesn't need data
    Data = data; 
    setupModelData(data, m_rootItem);
}

TreeModel::~TreeModel() {
    delete m_rootItem;
}

void TreeModel::setupModelData(DataSetCollection *data, TreeItem* parent) {
    for (auto it = data->begin(); it != data->end(); ++it) {
        TreeItem* dateItem = new TreeItem(it.key(), parent); // Parent item: QDate
        parent->appendChild(dateItem);

        for (int i=0; i<it.value().count(); i++) {
            TreeItem* childItem = new TreeItem(it.value().at(i).Sample_Number, dateItem);
            dateItem->appendChild(childItem);
        }
    }
}

int TreeModel::columnCount(const QModelIndex& parent) const {
    return 1; // We only display the data (QDate or int) in one column
}

int TreeModel::rowCount(const QModelIndex& parent) const {
    TreeItem* parentItem = !parent.isValid() ? m_rootItem : static_cast<TreeItem*>(parent.internalPointer());
    return parentItem->childCount();
}

QVariant TreeModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex& index) const {
    return index.isValid() ? Qt::ItemIsEnabled | Qt::ItemIsSelectable : Qt::NoItemFlags;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return "Data";  // Can be adjusted for more meaningful header

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem* parentItem = !parent.isValid() ? m_rootItem : static_cast<TreeItem*>(parent.internalPointer());
    TreeItem* childItem = parentItem->child(row);

    return childItem ? createIndex(row, column, childItem) : QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex& index) const {
    if (!index.isValid())
        return QModelIndex();

    TreeItem* childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem* parentItem = childItem->parentItem();

    return parentItem == m_rootItem ? QModelIndex() : createIndex(parentItem->row(), 0, parentItem);
}
