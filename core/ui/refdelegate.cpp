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

#include "refdelegate.h"

#include <model/treeitem.h>
#include <model/msptypeinfo.h>

#include <QtGui/QPainter>


RefDelegate::RefDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void RefDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    TreeItem * item = static_cast<TreeItem *>( index.internalPointer() );
    if (MSPTypeInfo::instance().matchedType( item->type() ) == "__HEADER__")
    {
        // draw background of header items
        painter->save();

        QLinearGradient g(0, 0, option.rect.width(), 0);
        g.setColorAt(0, QColor(0, 0, 0, 0));
        g.setColorAt(1, QColor(56, 84, 121));

        painter->fillRect(option.rect, QBrush(g));

        painter->restore();
    }

    // draw default background
    QStyledItemDelegate::paint(painter, option, index);
}
