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

#include "treeitem.h"


TreeItem::TreeItem(const QString &name)
    : _parent(0)
    , _name(name)
{
}

TreeItem::~TreeItem()
{
    qDeleteAll(_children);
}

const QString & TreeItem::acceptedChildTypes() const
{
    return _acceptedChildTypes;
}

void TreeItem::setAcceptedChildTypes(const QString &types)
{
    _acceptedChildTypes = types;
}

QString TreeItem::pathSeparator() const
{
    return _pathSeparator;
}

void TreeItem::setPathSeparator(const QString &sep)
{
    _pathSeparator = sep;
}

QString TreeItem::text() const
{
    if (_text.isEmpty())
        return _name;

    return _text;
}

void TreeItem::setText(const QString &text)
{
    _text = text;
}

QString TreeItem::description() const
{
    return _description;
}

void TreeItem::setDescription(const QString &description)
{
    _description = description;
}

QIcon TreeItem::icon() const
{
    return _icon;
}

void TreeItem::setIcon(const QIcon &icon)
{
    _icon = icon;
}

TreeItem *TreeItem::parent() const
{
    return _parent;
}

void TreeItem::setParent(TreeItem *newParent)
{
    if ( _parent == newParent )
        return;

    // move from old to new parent
//    reparent(newParent)
//    if ( _parent != 0 )
//    {
//        _parent->removeChild(this);
//        if (newParent != 0)
//            newParent->appendChild(this);
//    }

    _parent = newParent;
}

const QList<TreeItem *> &TreeItem::children() const
{
    return _children;
}

TreeItem * TreeItem::appendChild(TreeItem *child)
{
    // when a child with name exists, return it instead of creating a new one
    int existingChildIndex = indexOf(child->name());
    if (existingChildIndex >= 0)
        return _children[existingChildIndex];

    // create new child
    child->setParent(this);
    _children.append(child);

    return child;
}

TreeItem * TreeItem::appendChild(const QString &path)
{
    if ( QRegExp(_acceptedChildTypes).indexIn(path) != 0 )
        return 0;

    // seperate a path into subitems
    if (!_pathSeparator.isEmpty())
        return seperatePath(path);

    TreeItem * child = appendChild(new TreeItem(path));
    return child;
}

void TreeItem::removeChild(TreeItem *child)
{
    _children.removeOne(child);
    child->setParent(0);
}

int TreeItem::row()
{
    if (_parent == 0)
        return 0;

    return _parent->children().indexOf(this);
}

QString TreeItem::name(bool fullName) const
{
    if (_name.isEmpty())
        return "< ! INVALID ! >";

//    if (fullName)
//        return fullName();

    return _name;
}

void TreeItem::setName(const QString &name)
{
    //! @todo still a little unclear how to split name pathes here
    _name = name;
}

TreeItem * TreeItem::seperatePath(QString name)
{
    const QIcon folderIcon = QIcon(":/icons/folder.png");
    name.remove(QRegExp(acceptedChildTypes()));
    QStringList subNames = name.split(QRegExp(_pathSeparator));

    // create parent item
    TreeItem *first = TreeItem::appendChild(new TreeItem(subNames.takeFirst()));

    TreeItem *sub = first;
    while (!subNames.isEmpty())
    {
        // set icon to previous item
        sub->setIcon(folderIcon);

        // set name and create next subitem
        sub = sub->appendChild(subNames.takeFirst());
    }

    return first;
}

int TreeItem::indexOf(const QString &name) const
{
    int i = 0;
    bool found = false;
    while (!found && (i < _children.count()))
    {
        found = (_children[i]->name() == name);
        if (!found)
            ++i;
    }

    // found child item?
    if ( i < _children.count() )
        return i;

    return -1;
}
