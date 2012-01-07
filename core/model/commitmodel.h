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

#ifndef COMMITMODEL_H
#define COMMITMODEL_H

#include <QtCore/QAbstractItemModel>
#include <QtCore/QStringList>

#include <src/qgitcommit.h>

//namespace LibQGit2
//{
//    class QGitCommit;
//}

/**
  @brief Represents a commit history model. Currently Git only, but support for other VCS is planned for the future.
  */
class CommitModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CommitModel(QObject *parent = 0);
    ~CommitModel();

    /**
      Get data from a @see QGitCommit to edit or view a commit.
      @todo For the beginning, only the display role should be used here. Goal is to use a QItemDelegate later on.
      */
    QVariant data(const QModelIndex& index, int role) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& index) const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    /**
      Sets the commit pointing to HEAD. This is the 'root'.
      */
    void setHeadCommit(const LibQGit2::QGitCommit &commit);

private:
    QList<LibQGit2::QGitCommit>     _commits;
    QStringList                     _headers;

    /**
      Helper function to retreive the correct text for the column specified by the model index.
      */
    QVariant commitData(int col, const LibQGit2::QGitCommit *commit) const;
};

#endif // COMMITMODEL_H
