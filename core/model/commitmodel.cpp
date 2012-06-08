/**
**    Copyright (c) 2011 by Nils Fenner
**
**    This file is part of MsPiggit.
**
**    MsPiggit is free software: you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**    MsPiggit is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with MsPiggit.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "commitmodel.h"

#include <src/qgitrepository.h>
#include <src/qgitsignature.h>
#include <src/qgitrevwalk.h>

#include <model/msptypeinfo.h>

#include <QtGui/QLinearGradient>

using namespace LibQGit2;


CommitModel::CommitModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    _headers << tr("Message")
             << tr("Author")
             << tr("email")
             << tr("Date")
             << tr("Id")
                ;
}

CommitModel::~CommitModel()
{
}

QVariant CommitModel::data(const QModelIndex &index, int role) const
{
    // check on valid QModelIndex
    if (!index.isValid())
        return QVariant();

    QGitCommit * commit = static_cast<QGitCommit *>(index.internalPointer());

    if (role == Qt::DisplayRole)
    {
        return commitData(index.column(), commit);
    }

    else if (role == Qt::BackgroundRole)
    {
        if (commit->oid() == commit->owner().head().oid())
        {
            //! @todo Outsource to CommitDelegate
            QLinearGradient g(0, 0, 0, 30);
            g.setColorAt(0, QColor(255, 255, 255, 0));
            g.setColorAt(.5, QColor(255, 181, 79));
            g.setColorAt(1, QColor(255, 255, 255, 0));
            return QBrush(g);
        }
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
    if ( (orientation == Qt::Horizontal) && (role == Qt::DisplayRole)
         &&  (_headers.count() > section) )
    {
        return _headers[section];
    }

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

    return createIndex(row, column, const_cast<QGitCommit *>(parentCommit));
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
    Q_UNUSED(parent)
    return _commits.count();
}

int CommitModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    //! @todo Return the selected header count for commits.
    return _headers.count();
}

/**
  Setup the commit model starting with the HEAD commit.
  */
void CommitModel::setHeadCommit(const QGitCommit &commit)
{
    beginResetModel();

    _commits.clear();

    if (!commit.isNull())
        walkCommits(commit);

    //! @todo Read all commits using lazy loading. Cache is required for large repositories!

    endResetModel();

    emit initialized();
}

void CommitModel::walkCommits(const QGitCommit &head)
{
    // read all commits from _headCommit downwards
    QGitRevWalk walker(head.owner());
    walker.setSorting(QGitRevWalk::Topological | QGitRevWalk::Time);

    walker.push(head); // initialize the walker

    // walk revisions
    QGitCommit c;
    while ( walker.next(c) )
    {
        _commits.append(c);
    }
}

/**
  Help function to get the commit data.
  */
QVariant CommitModel::commitData(int col, const QGitCommit *commit) const
{
    switch (col)
    {
    default: return QVariant();

    case 0: return commit->shortMessage();
    case 1: return commit->author().name();
    case 2: return commit->author().email();
    case 3: return commit->dateTime();
    case 4: return QString( commit->oid().format() );
    }
}
