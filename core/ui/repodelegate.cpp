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

#include "repodelegate.h"

#include <metatypes.h>

#include <model/treeitem.h>
#include <model/modelaccess.h>

#include <QtCore/QEvent>
#include <QtGui/QMessageBox>

#include <QGit2/QGitError>


RepoDelegate::RepoDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

bool RepoDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    using namespace LibQGit2;

    TreeItem *item = static_cast<TreeItem*>( index.internalPointer() );

    if ( event->type() == QEvent::MouseButtonDblClick
         )
    {
        event->accept();

        if (item->type() == "repo")
        {
            ModelAccess::instance().reinitialize( item->data().value<QGitRepository>() );
        }

        else if (item->type() == "subrepo")
        {
            const QGitSubmodule &submodule = item->data().value<QGitSubmodule>();
            if ( !ModelAccess::instance().reinitialize(submodule.repository()) )
            {
                QMessageBox::warning( 0, tr("Cannot display repository.")
                                      , tr("Cannot display repository:\n%1").arg(QGitError::lastMessage())
                                      );
            }
        }

        return true;
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
