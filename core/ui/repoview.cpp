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

#include "repoview.h"
#include "ui_repoview.h"

#include <model/modelaccess.h>
#include <model/commitmodel.h>
#include <model/referencemodel.h>

#include <ui/refdelegate.h>

#include <QtGui/QMessageBox>


RepoView::RepoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RepoView)
{
    ui->setupUi(this);

#ifdef Q_OS_MACX
    ui->treeRepoRefs->setAttribute(Qt::WA_MacShowFocusRect, 0);
#endif

    layout()->setContentsMargins(3, 3, 3, 3);

    ModelAccess &repoModels = ModelAccess::instance();

    // setup the views/models
    ui->tableCommits->setModel( repoModels.commitModelPtr() );
    ui->tableCommits->horizontalHeader()->setHighlightSections(false);
    ui->tableCommits->horizontalHeader()->setMovable(true);

    connect(repoModels.commitModelPtr(), SIGNAL(initialized()), ui->tableCommits, SLOT(resizeColumnsToContents()));

    ui->treeRepoRefs->setModel( repoModels.refModelPtr() );
    ui->treeRepoRefs->setItemDelegate(new RefDelegate());
}

RepoView::~RepoView()
{
    delete ui;
}
