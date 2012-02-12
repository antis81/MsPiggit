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

#ifndef TREEITEM_H
#define TREEITEM_H

#include <QtCore/QStringList>
#include <QtGui/QIcon>

/**
  * @brief Generic data structure holding an item of a hierarchical tree.
  */
template <typename T>
class TreeItem
{
public:
    typedef T TDataType;
    typedef T * TDataTypePtr;

    explicit TreeItem(const QString &name, TDataTypePtr data = 0)
        : _data(data)
        , _parent(0)
        , _name(name)
    {
    }

    virtual ~TreeItem()
    {
        qDeleteAll(_children);
    }

    const QString &acceptedChildTypes() const
    {
        return _acceptedChildTypes;
    }

    void setAcceptedChildTypes(const QString &types)
    {
        _acceptedChildTypes = types;
    }

    QString pathSeparator() const
    {
        return _pathSeparator;
    }

    void setPathSeparator(const QString &sep)
    {
        _pathSeparator = sep;
    }

    QString name(bool fullName = false) const
    {
        if (_name.isEmpty())
            return "< ! INVALID ! >";

    //    if (fullName)
    //        return fullName();

        return _name;
    }

    void setName(const QString &name)
    {
        //! @todo still a little unclear how to split name pathes here
        _name = name;
    }

    QString text() const
    {
        if (_text.isEmpty())
            return _name;

        return _text;
    }

    void setText(const QString &text)
    {
        _text = text;
    }

    QString description() const
    {
        return _description;
    }

    void setDescription(const QString &description)
    {
        _description = description;
    }

    QIcon icon() const
    {
        return _icon;
    }

    void setIcon(const QIcon &icon)
    {
        _icon = icon;
    }

    TreeItem<TDataType> *parent() const
    {
        return _parent;
    }

    void setParent(TreeItem<TDataType> *newParent)
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

    const QList<TreeItem<TDataType> *> &children() const
    {
        return _children;
    }

    virtual TreeItem<TDataType> *appendChild(const QString &path)
    {
        if ( QRegExp(_acceptedChildTypes).indexIn(path) != 0 )
            return 0;

        // seperate a path into subitems
        if (!_pathSeparator.isEmpty())
            return seperatePath(path);

        TreeItem<TDataType> * child = appendChild(new TreeItem<TDataType>(path));
        return child;
    }

    void removeChild(TreeItem<TDataType> * child)
    {
        _children.removeOne(child);
        child->setParent(0);
    }

    int row()
    {
        if (_parent == 0)
            return 0;

        return _parent->children().indexOf(this);
    }

    int indexOf(const QString &name) const
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

    /**
      * @returns a const reference to the data object
      */
    const TDataTypePtr data() const
    {
        return _data;
    }

protected:
    TreeItem<TDataType> * appendChild(TreeItem<TDataType> *child)
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

private:
    TDataTypePtr                    _data; //!< pointer to a generic data structure

    TreeItem<TDataType> *           _parent;
    QList<TreeItem<TDataType> *>    _children;
    QString                         _acceptedChildTypes;
    QString                         _pathSeparator; //!< regular expression string to separate the item into a path structure

    QString     _text;
    QString     _description;
    QIcon       _icon;
    QString     _name; //!< the items name is used as it's id it can be part of a path.
    //QString     _fullName;

    TreeItem<TDataType> *seperatePath(QString name)
    {
        const QIcon folderIcon = QIcon(":/icons/folder.png");
        name.remove(QRegExp(acceptedChildTypes()));
        QStringList subNames = name.split(QRegExp(_pathSeparator));

        // create parent item
        TreeItem<TDataType> *first = appendChild(new TreeItem<TDataType>(subNames.takeFirst()));

        TreeItem<TDataType> *sub = first;
        while (!subNames.isEmpty())
        {
            // set icon to previous item
            sub->setIcon(folderIcon);

            // set name and create next subitem
            sub = sub->appendChild(subNames.takeFirst());
        }

        return first;
    }

};

#endif // TREEITEM_H
