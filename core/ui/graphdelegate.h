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

#ifndef COMMITDELEGATE_H
#define COMMITDELEGATE_H

#include <QtGui/QItemDelegate>

class CommitModel;

namespace LibQGit2
{
    class QGitCommit;
}

class GraphDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit GraphDelegate(const CommitModel &model, QObject *parent = 0);

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:
    
public slots:

private:
    const int margin;
    const CommitModel &     _model;

    const LibQGit2::QGitCommit * commitFromIndex(const QModelIndex &index) const;
};

#endif // COMMITDELEGATE_H
