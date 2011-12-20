#include "submodulemodel.h"

#include <QtCore/QFileInfo>
#include <QtCore/QDir>

#include <model/treeitem.h>
#include <src/qgitrepository.h>


SubmoduleModel::SubmoduleModel(QObject *parent)
    : QAbstractItemModel(parent)
    , _mainRepoItem(0)
{
}

QVariant SubmoduleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem * item = static_cast<TreeItem *>(index.internalPointer());

    if (role == Qt::DisplayRole)
    {
        return item->text();
    }
    else if (role == Qt::DecorationRole)
    {
        return item->icon();
    }
    else if (role == Qt::ToolTipRole)
    {
        return item->description();
    }
//    else if (role == Qt::BackgroundRole)
//    {
//        return QColor(0x00, 0x00, 0xFF, 0x20);
//    }

    return QVariant();
}

Qt::ItemFlags SubmoduleModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant SubmoduleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section != 0)
        return QVariant();

    if ((orientation == Qt::Horizontal) && (role == Qt::DisplayRole))
        return tr("Repositories");

    return QVariant();
}

QModelIndex SubmoduleModel::index(int row, int column, const QModelIndex &parent) const
{
    if ( !hasIndex(row, column, parent) )
        return QModelIndex();

    if ( !parent.isValid() )
    {
        if (_mainRepoItem != 0)
            return createIndex(row, column, _mainRepoItem);
    }
    else
    {
        // there is a parent - must be a treeitem
        TreeItem * parentItem = static_cast<TreeItem *>(parent.internalPointer());
        TreeItem * childItem = parentItem->children()[row];
        if (childItem != 0)
            return createIndex(row, column, childItem);
    }

    return QModelIndex();
}

QModelIndex SubmoduleModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem *>(index.internalPointer());
    if (childItem == 0)
        return QModelIndex();

    TreeItem *parentItem = childItem->parent();
    if (parentItem == 0)
        return QModelIndex();

    // get the row of the parent item by using the parents parent item
    return createIndex(parentItem->row(), 0, parentItem);
}

int SubmoduleModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 1;

    return static_cast<TreeItem *>(parent.internalPointer())->children().count();
}

int SubmoduleModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 1;
}

void SubmoduleModel::initialize(const LibQGit2::QGitRepository &repo)
{
    beginResetModel();

    delete _mainRepoItem;
    _mainRepoItem = new TreeItem( repo.name() );

    endResetModel();
}
