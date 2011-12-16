#include "referencemodel.h"

#include "src/qgitrepository.h"
#include "model/headeritem.h"


ReferenceModel::ReferenceModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant ReferenceModel::data(const QModelIndex &index, int role) const
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

Qt::ItemFlags ReferenceModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ReferenceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section != 0)
        return QVariant();

    if ((orientation == Qt::Horizontal) && (role == Qt::DisplayRole))
        return tr("References");

    return QVariant();
}

QModelIndex ReferenceModel::index(int row, int column, const QModelIndex &parent) const
{   
    if ( !hasIndex(row, column, parent) )
        return QModelIndex();

    if ( !parent.isValid() )
    {
        return createIndex(row, column, _headers[row]);
    }
    else
    {
        TreeItem * parentItem;
        parentItem = static_cast<TreeItem *>(parent.internalPointer());

        // there is a parent - must be a treeitem
        TreeItem * childItem = parentItem->children()[row];
        if (childItem != 0)
            return createIndex(row, column, childItem);
    }

    return QModelIndex();
}

QModelIndex ReferenceModel::parent(const QModelIndex &index) const
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

int ReferenceModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return _headers.count();

    return static_cast<TreeItem *>(parent.internalPointer())->children().count();
}

int ReferenceModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 1;
}

void ReferenceModel::setupRefs(const LibQGit2::QGitRepository &repo)
{
    beginResetModel();

    qDeleteAll(_headers);
    _headers.clear();

    HeaderItem * branchItem = new HeaderItem("^(refs/heads/)");
    branchItem->setText("Branches");
    branchItem->setIcon( QIcon(":/icons/branch.png") );
    branchItem->setDescription( tr("The active repositories branches.") );
    branchItem->setPathSeparator("/");

    HeaderItem * remoteItem = new HeaderItem( "^(refs/remotes/)" );
    remoteItem->setText("Remotes");
    remoteItem->setIcon( QIcon(":/icons/remote.png") );
    remoteItem->setDescription( tr("The active repositories remote references.") );
    remoteItem->setPathSeparator("/");

    HeaderItem * tagItem = new HeaderItem("^(refs/tags/)");
    tagItem->setText("Tags");
    tagItem->setIcon( QIcon(":/icons/tag.png") );
    tagItem->setDescription( tr("The active repositories version tags.") );
    tagItem->setPathSeparator("[/\\._-]");

    _headers << branchItem << remoteItem << tagItem;

    setupBranches(repo);

    endResetModel();
}

void ReferenceModel::setupBranches(const LibQGit2::QGitRepository &repo)
{
    //! @todo this is a list of all references, filter by branches
    QStringList refs = repo.listReferences();
    while (!refs.isEmpty())
    {
        // try to match the item by it's filter prefix
        int i = 0;
        TreeItem * toAdd = 0;
        while ( (toAdd == 0) && (i < _headers.count()) )
        {
            toAdd = _headers[i]->appendChild(refs.first());
            ++i;
        }

        refs.removeFirst();
    }
}
