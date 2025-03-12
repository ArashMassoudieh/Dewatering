#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QDate>
#include <vector>

class TreeItem {
public:
    explicit TreeItem(const QVariant& data, TreeItem* parentItem = nullptr);
    ~TreeItem();

    void appendChild(TreeItem* child);
    TreeItem* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem* parentItem();

private:
    QVariant m_itemData;
    TreeItem* m_parentItem;
    std::vector<TreeItem*> m_childItems;
};

#endif // TREEITEM_H


