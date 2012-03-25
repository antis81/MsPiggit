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

#include "referencemodel.h"

#include <src/qgitrepository.h>
#include <model/treeitem.h>
#include <model/treebuilder.h>
#include <model/msptypeinfo.h>

#include <QtGui/QLinearGradient>


Q_DECLARE_METATYPE( LibQGit2::QGitRef )


ReferenceModel::ReferenceModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant ReferenceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem * item = static_cast<TreeItem *>(index.internalPointer());

    if (role == Qt::DisplayRole)
    {
        return QString("%1").arg(item->text());
    }
    else if (role == Qt::DecorationRole)
    {
        return MSPTypeInfo::instance().value(item->type(), "icon");
    }
    else if (role == Qt::ToolTipRole)
    {
        return MSPTypeInfo::instance().value(item->type(), "tooltip");
    }
    else if (role == Qt::ForegroundRole)
    {
        if ( item->data().canConvert<LibQGit2::QGitRef>() )
        {
            const LibQGit2::QGitRef & ref = item->data().value<LibQGit2::QGitRef>();
            if ( _repo.head().oid() == ref.oid() )
            {
                return QColor(0xFF, 0x85, 0x00, 0xFF);
            }
        }
    }

    return QVariant();
}

Qt::ItemFlags ReferenceModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = Qt::ItemIsEnabled;

    if (!index.isValid())
        return Qt::NoItemFlags;

    TreeItem * item = static_cast<TreeItem *>(index.internalPointer());
    if ( MSPTypeInfo::instance().matchedType(item->type()) != "__HEADER__" )
        flags |= Qt::ItemIsSelectable;

    return flags;
}

QVariant ReferenceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section != 0)
        return QVariant();

    if ((orientation == Qt::Horizontal) && (role == Qt::DisplayRole))
        return tr("References");

    return QVariant();
}

QModelIndex ReferenceModel::index(int row, int column, const QModelIndex &parent) const
{   
    if ( !hasIndex(row, column, parent) )
        return QModelIndex();

    if ( !parent.isValid() )
    {
        return createIndex(row, column, _headers[row]);
    }
    else
    {
        TreeItem * parentItem;
        parentItem = static_cast<TreeItem *>(parent.internalPointer());

        // there is a parent - must be a treeitem
        TreeItem * childItem = parentItem->children()[row];
        if (childItem != 0)
            return createIndex(row, column, childItem);
    }

    return QModelIndex();
}

QModelIndex ReferenceModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem *>(index.internalPointer());
    if (childItem == 0)
        return QModelIndex();

    TreeItem *parentItem = childItem->parent();
    if (parentItem == 0)
        return QModelIndex();

    // get the row of the parent item by using the parents parent item
    return createIndex(parentItem->row(), 0, parentItem);
}

int ReferenceModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return _headers.count();

    return static_cast<TreeItem *>(parent.internalPointer())->children().count();
}

int ReferenceModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 1;
}

void ReferenceModel::setupRefs(const LibQGit2::QGitRepository &repo)
{
    beginResetModel();

    qDeleteAll(_headers);
    _headers.clear();

    TreeItem * branchItem = new TreeItem("__HEADER_BRANCHES__");
    branchItem->setAcceptedTypes( QStringList() << "__FOLDER__" << "ref_branch" );
    branchItem->setText("Branches");

    TreeItem * remoteItem = new TreeItem("__HEADER_REMOTES__");
    remoteItem->setAcceptedTypes( QStringList() << "__FOLDER__" << "ref_remote" );
    remoteItem->setText("Remotes");

    TreeItem * tagItem = new TreeItem("__HEADER_TAGS__");
    tagItem->setAcceptedTypes( QStringList() << "__FOLDER__" << "ref_tag" );
    tagItem->setText("Tags");
//    tagItem->setPathSeparator("[/\\._-]");

    _headers << branchItem << remoteItem << tagItem;

    setupBranches(repo);

    endResetModel();
}

void ReferenceModel::setupBranches(const LibQGit2::QGitRepository &repo)
{
    _repo = repo;
    QStringList refs = repo.listReferences();
    while (!refs.isEmpty())
    {
        QString candidate = refs.takeFirst();
        QString type = MSPTypeInfo::instance().matchedType(candidate);

        // try to match the item by it's filter prefix
        int i = 0;
        while ( i < _headers.count() )
        {
            if ( _headers.at(i)->accepts(type) )
            {
                TreeItem * item = new TreeItem( type, QVariant::fromValue(repo.lookupRef(candidate)) );

                candidate.remove(QRegExp("^(refs/\\w*/)"));
                TreeBuilder::instance().insertItem(item, _headers[i], candidate, "");
            }
            ++i;
        }
    }
}
