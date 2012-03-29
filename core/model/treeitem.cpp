#include "treeitem.h"

#include <model/msptypeinfo.h>


TreeItem::TreeItem(const QString &type, const QVariant &data)
    : _parent(0)
    , _type(type)
    , _data(data)
{
}

TreeItem *TreeItem::parent() const
{
    return _parent;
}

void TreeItem::setParent(TreeItem *newParent)
{
    // reparent item when parent was set
//    if (_parent != newParent)
//    {
//        _parent->removeChild(this);
//        _parent->appendChild(this);
//    }

    _parent = newParent;
}

const QList<TreeItem *> &TreeItem::children() const
{
    return _children;
}

bool TreeItem::accepts(const QString &type) const
{
    bool accepted = false;

    int i = 0;
    while (!accepted && (i < _acceptedTypes.count()))
    {
        QString TEST = _acceptedTypes.at(i);
        accepted = (type == _acceptedTypes.at(i));
        ++i;
    }

    return accepted;
}

const QStringList &TreeItem::acceptedTypes() const
{
    return _acceptedTypes;
}

void TreeItem::setAcceptedTypes(const QStringList &types)
{
    _acceptedTypes = types;
}

void TreeItem::appendChild(TreeItem *item)
{
    item->setParent(this);
    _children.append(item);
}

TreeItem* TreeItem::findTextItem(const QString &text) const
{
    TreeItem *  result = 0;
    int i = 0;
    while ( (result == 0) && (i < _children.count()) )
    {
        if (_children[i]->text() == text)
            result = _children[i];

        ++i;
    }

    return result;
}

QString TreeItem::type() const
{
    return _type;
}

int TreeItem::row()
{
    if (_parent == 0)
        return 0;

    return _parent->children().indexOf(this);
}

const QVariant & TreeItem::data() const
{
    return _data;
}

QString TreeItem::text() const
{
    return _text;
}

void TreeItem::setText(QString text)
{
    _text = text;
}
