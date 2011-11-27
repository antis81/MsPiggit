#include "commitmodel.h"

#include <src/qgitrepository.h>
#include <src/qgitsignature.h>
#include <src/qgitrevwalk.h>

using namespace LibQGit2;


CommitModel::CommitModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

CommitModel::~CommitModel()
{
}

QVariant CommitModel::data(const QModelIndex &index, int role) const
{
    // check on valid QModelIndex
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        QGitCommit * commit( static_cast<QGitCommit *>(index.internalPointer()) );

        return commit->message();
    }

    // Request for unhandled data role
    return QVariant();
}

Qt::ItemFlags CommitModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant CommitModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)

    if ((orientation == Qt::Horizontal)
            && (role == Qt::DisplayRole))
        return "Column";

    return QVariant();
}

QModelIndex CommitModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (row >= _commits.count())
        return QModelIndex();

    const QGitCommit *  parentCommit = 0;

    if (!parent.isValid())
        parentCommit = &(_commits.at(row));
    else
        parentCommit = static_cast<QGitCommit *>(parent.internalPointer());

    if (parentCommit == 0)
        return QModelIndex();

    return createIndex(row, 0, const_cast<QGitCommit *>(parentCommit));
}

QModelIndex CommitModel::parent(const QModelIndex &index) const
{
    return QModelIndex();

    if (!index.isValid())
        return QModelIndex();

    QGitCommit * childCommit( static_cast<QGitCommit *>(index.internalPointer()) );

    if (childCommit->isNull())
        return QModelIndex();

    QGitCommit parentCommit = childCommit->parent(0);
    if ( (parentCommit.data() == NULL) )
        return QModelIndex();

    return QModelIndex();// createIndex(parent.row(), 0, &parentCommit);
}

int CommitModel::rowCount(const QModelIndex &parent) const
{
    return _commits.count();
}

int CommitModel::columnCount(const QModelIndex &parent) const
{
    //! @todo Return the selected header count for commits.
    return 1;
}

void CommitModel::setHeadCommit(const QGitCommit &commit)
{
    if (commit.isNull())
        return;

    beginResetModel();

    _commits.clear();
//    _headCommit = commit;

    //! @todo Read all commits using lazy loading. Cache is required for large repositories!
    // read all commits from _headCommit downwards

    QGitRevWalk walker(commit.owner());
    walker.setSorting(QGitRevWalk::Topological | QGitRevWalk::Time);

    walker.push(commit); // initialize the walker

    // walk revisions
    QGitCommit c;
    while ( walker.next(c) )
    {
        _commits.append(c);
    }

    endResetModel();
}
