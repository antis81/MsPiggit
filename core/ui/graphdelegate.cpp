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

#include "graphdelegate.h"

#include <QtGui/QPainter>

#include <src/qgitcommit.h>
#include <src/qgitrepository.h>
#include <src/qgitrevwalk.h>

#include <model/commitmodel.h>

using namespace LibQGit2;


GraphDelegate::GraphDelegate(const CommitModel &model, QObject *parent)
    : QItemDelegate(parent)
    , _model(model)
    , margin(3)
{
}

void GraphDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);

    // alter the draw rect bounds
    const_cast<QStyleOptionViewItem &>(option).rect.adjust(margin, 0, 0, 0);

    // pen to draw the outlines
    QPen outLinePen;
    outLinePen.setWidthF(1.0);
    painter->setPen(outLinePen);

    // fill color for commit circle
    painter->setBrush(Qt::white);

    const QModelIndex prevIndex = index.sibling(index.row()-1, index.column());
    const QModelIndex nextIndex = index.sibling(index.row()+1, index.column());

    const QGitCommit *commit = static_cast<const QGitCommit *>( index.internalPointer() );
    const QGitCommit *prevCommit = commitFromIndex(prevIndex);
    const QGitCommit *nextCommit = commitFromIndex(nextIndex);

    // offset constants
    const int leftOffset = option.rect.left() + margin;
    const int radius = 4;
    const int laneDistance = 4 * radius;
    const int rowCenter = option.rect.center().y();

    const int commitParentCnt = commit->parentCount();

    int laneCol = 0;
    if ((commitParentCnt > 0) && (prevCommit != 0) && (commit->parentId(0) != prevCommit->oid()) )
        ++laneCol;

    const QPoint laneCenter = QPoint(leftOffset + (laneDistance * laneCol), rowCenter);

    // draw lane span
    if (commitParentCnt > 1)
        painter->drawLine(laneCenter, QPoint(laneCenter.x() + (commitParentCnt * laneDistance), rowCenter));

    // draw circle
    painter->drawEllipse( laneCenter, radius, radius );

    painter->restore();

    int textXOffset = (qMax(1, (int)commitParentCnt) + laneCol) * laneDistance;

    // alter draw rect bounds
    const_cast<QStyleOptionViewItem &>(option).rect.adjust(textXOffset, 0, 0, 0);
    QItemDelegate::paint(painter, option, index);
}

const QGitCommit *GraphDelegate::commitFromIndex(const QModelIndex &index) const
{
    if (index.isValid())
        return 0;

    return static_cast<QGitCommit *>( index.internalPointer() );
}
