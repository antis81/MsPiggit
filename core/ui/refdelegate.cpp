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
