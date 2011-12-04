#include "referencemodel.h"

#include "src/qgitrepository.h"

using namespace LibQGit2;


ReferenceModel::ReferenceModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    _headers << HeaderItem("Branches", QIcon(":/icons/branch.png")
                           , tr("The active repositories branches."));
    _headers << HeaderItem("Remotes", QIcon(":/icons/remote.png")
                           , tr("The active repositories remote references."));
    _headers << HeaderItem("Tags", QIcon(":/icons/tag.png")
                           , tr("The active repositories version tags."));
}

QVariant ReferenceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    HeaderItem * item = static_cast<HeaderItem *>(index.internalPointer());

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
    return Qt::ItemIsEnabled;
}

QVariant ReferenceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((orientation == Qt::Horizontal) && (role == Qt::DisplayRole))
    {
        return tr("References");
    }

    return QVariant();
}

QModelIndex ReferenceModel::index(int row, int column, const QModelIndex &parent) const
{
    if ( !hasIndex(row, column, parent) || (row >= _headers.count()) )
        return QModelIndex();

    const HeaderItem * item = &(_headers.at(row));

    return createIndex(row, column, const_cast<HeaderItem *>(item));
}

QModelIndex ReferenceModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int ReferenceModel::rowCount(const QModelIndex &parent) const
{
    return 3;
}

int ReferenceModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

void ReferenceModel::setupRefs(const QGitRepository &repo)
{
    beginResetModel();

    //repo.lookupRef()
    //_refs <<

    endResetModel();
}
