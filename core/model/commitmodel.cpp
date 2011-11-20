#include "commitmodel.h"

using namespace LibQGit2;


CommitModel::CommitModel(const QGitCommit &commit, QObject *parent)
    : QAbstractItemModel(parent)
    , _headCommit(commit)
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
        return _headCommit.message();

    return QVariant();
}

QModelIndex CommitModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    const QGitCommit *    parentCommit;

    if (!parent.isValid())
        parentCommit = &_headCommit;
    else
        parentCommit = static_cast<QGitCommit *>(parent.internalPointer());

    if (!parentCommit)
        return QModelIndex();

    if (row < 0 || row >= parentCommit->parentCount())
        return QModelIndex();

    QGitCommit childItem = parentCommit->parent(row);
    if (childItem.data() != NULL)
        return createIndex(row, column, &childItem);
    else
        return QModelIndex();
}

QModelIndex CommitModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    QGitCommit * childCommit( static_cast<QGitCommit *>(index.internalPointer()) );

    if (childCommit->data() == NULL)
        return QModelIndex();

    QGitCommit parentCommit = childCommit->parent(0);
    if ( (parentCommit.data() == NULL) || (parentCommit.data() == _headCommit.data()) )
        return QModelIndex();

    return QModelIndex();// createIndex(parent.row(), 0, &parentCommit);
}

int CommitModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid() || _headCommit.isNull())
        return 0;

    //! @todo Return the real commit count.
    return 2 + _headCommit.parentCount();
}

int CommitModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid() || _headCommit.isNull())
        return 0;

    //! @todo Return the selected header count for commits.
    return 1;
}

void CommitModel::setHeadCommit(const QGitCommit &commit)
{
    _headCommit = commit;
    //! @todo Update the view!
}
