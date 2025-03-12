#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>
#include <treemodel.h>
#include <QDebug>

class TreeView : public QTreeView {
    Q_OBJECT

public:
    explicit TreeView(QWidget *parent = nullptr) : QTreeView(parent) {
        connect(this, &QTreeView::clicked, this, &TreeView::onItemClicked);
    }

private slots:
    void onItemClicked(const QModelIndex &index) {
        auto model = static_cast<TreeModel *>(this->model());
        if (model) {
            QString key = model->data(index,Qt::DisplayRole).toString();
            qDebug() << "Clicked Key:" << key;
        }
    }
};

#endif // TREEVIEW_H
