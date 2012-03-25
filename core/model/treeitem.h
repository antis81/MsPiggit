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
#include <QtCore/QVariant>



/**
  * @brief Data structure holding an item of a hierarchical tree.
  */
class TreeItem
{
public:
    explicit TreeItem(const QString &type, const QVariant &data = QVariant());

    TreeItem * parent() const;
    void setParent(TreeItem *newParent);
    const QList<TreeItem *> & children() const;

    bool accepts(const QString &type) const;
    const QStringList & acceptedTypes() const;
    void setAcceptedTypes(const QStringList &types);

    void appendChild(TreeItem *item);
    TreeItem *findTextItem(const QString &text) const;

    QString type() const;

    int row();

    /**
      * @returns a const reference to the data object
      */
    const QVariant & data() const;

    virtual QString text() const;
    void setText(QString text);

private:
    TreeItem *          _parent;
    QList<TreeItem *>   _children;

    QString             _type; //!< a unique type of the TreeItem
    QStringList         _acceptedTypes; //!< controls accepted types of subitems

    QString             _text;

    QVariant            _data; //!< the data of the TreeItem
};

#endif // TREEITEM_H
