#ifndef HEADERITEM_H
#define HEADERITEM_H

#include <model/treeitem.h>


/**
Describes a header item to use in a Tree-, Tablemodel.
*/
class HeaderItem : public TreeItem
{
public:
    explicit HeaderItem(const QString &filterPrefix);
};

#endif // HEADERITEM_H
