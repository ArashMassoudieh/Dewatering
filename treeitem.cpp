#include "TreeItem.h"

TreeItem::TreeItem(const QVariant& data, TreeItem* parentItem)
    : m_itemData(data), m_parentItem(parentItem) {
}

TreeItem::~TreeItem() {
    for (TreeItem* child : m_childItems)
        delete child;
}

void TreeItem::appendChild(TreeItem* child) {
    m_childItems.push_back(child);
}

TreeItem* TreeItem::child(int row) {
    return (row >= 0 && row < static_cast<int>(m_childItems.size())) ? m_childItems[row] : nullptr;
}

int TreeItem::childCount() const {
    return static_cast<int>(m_childItems.size());
}

int TreeItem::columnCount() const {
    return 1; // We have only one column for the data
}

QVariant TreeItem::data(int column) const {
    return column == 0 ? m_itemData : QVariant();
}

int TreeItem::row() const {
    if (m_parentItem) {
        auto it = std::find(m_parentItem->m_childItems.begin(), m_parentItem->m_childItems.end(), this);
        return it != m_parentItem->m_childItems.end() ? static_cast<int>(std::distance(m_parentItem->m_childItems.begin(), it)) : 0;
    }
    return 0;
}

TreeItem* TreeItem::parentItem() {
    return m_parentItem;
}
