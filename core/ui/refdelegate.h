#ifndef REFDELEGATE_H
#define REFDELEGATE_H

#include <QtGui/QStyledItemDelegate>

class RefDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit RefDelegate(QObject *parent = 0);
    
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // REFDELEGATE_H
