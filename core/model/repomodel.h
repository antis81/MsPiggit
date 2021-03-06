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

#ifndef REPOMODEL_H
#define REPOMODEL_H

#include <QtCore/QAbstractItemModel>
#include <QtCore/QSharedPointer>

class TreeItem;

namespace LibQGit2
{
    class QGitRepository;
    class QGitTree;
}

class RepoModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit RepoModel(QObject *parent = 0);
    
    /**
      Get data from a @see QGitReference to edit or view a reference (branch, tag, remote).
      @todo For the beginning, only the display role should be used here. Goal is to use a QItemDelegate later on.
      */
    QVariant data(const QModelIndex& index, int role) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& index) const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    void initialize(const LibQGit2::QGitRepository &repo);

private:
    TreeItem *      _mainRepoItem;

    /**
      * Reads all submodules recursive.
      */
    void parseSubmodules(TreeItem *parentItem, const LibQGit2::QGitRepository &repo);
};

#endif // REPOMODEL_H
