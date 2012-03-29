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

#include "repowindow.h"
#include "ui_repowindow.h"

#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QLabel>

#include <src/qgitrepository.h>
#include <src/qgitcommit.h>
#include <src/qgitexception.h>

#include <model/commitmodel.h>
#include <model/referencemodel.h>
#include <model/submodulemodel.h>

#include <ui/refdelegate.h>

using namespace LibQGit2;


RepoWindow::RepoWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RepoWindow)
{
    ui->setupUi(this);

    setupMainMenu();

    // setup the views
    ui->tableCommits->setModel(&_commitModel);
    ui->tableCommits->horizontalHeader()->setHighlightSections(false);
    ui->tableCommits->horizontalHeader()->setMovable(true);
    ui->treeRepoRefs->setModel(&_refModel);
    ui->treeRepoRefs->setItemDelegate(new RefDelegate());
    ui->treeSubmodules->setModel(&_submoduleModel);
}

RepoWindow::~RepoWindow()
{
    delete ui;
}

void RepoWindow::setupMainMenu()
{
    QMenu * m = ui->menuBar->addMenu("Repository");
    QAction * a = m->addAction("Open ...", this, SLOT(openRepository()));
    a->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    a->setShortcutContext(Qt::ApplicationShortcut);
}

void RepoWindow::openRepository()
{
    QFileDialog fd;
    fd.setFilter(QDir::AllDirs | QDir::Hidden);
    fd.setDirectory(QDir::home());
    fd.setWindowTitle( tr("Open a Repository") );
    if ( (fd.exec() != QDialog::Accepted) || fd.selectedFiles().isEmpty() )
        return;

    setupRepoView(fd.selectedFiles().first());
}

void RepoWindow::setupRepoView(QString path)
{
    if (path.isEmpty() || !checkDirExists(path))
        return;

    // open git repository and initialize views
    try
    {
        _repo.discoverAndOpen(path);
        updateWindowTitle( _repo );
    }
    catch (LibQGit2::QGitException e)
    {
        QMessageBox::critical( this, tr("Unable to open repository."), e.message() );
        return;
    }

    // setup the views
    initCommitHistory(_repo);
    initReferences(_repo);
    initSubmodules(_repo);
}

void RepoWindow::updateWindowTitle(const QGitRepository &repo)
{
    QString title = "Repository: " + repo.name();
    if ( repo.isBare() )
        title += QString(" (BARE)");
    setWindowTitle(title);
}

bool RepoWindow::checkDirExists(const QString &path) const
{
    QFileInfo fiRepo(path);
    if (!fiRepo.exists() || !fiRepo.isDir())
    {
        QMessageBox::critical(0, QObject::tr("Repository path not found."),
                              QObject::tr("The repositories path is not valid:\n%1").arg(path));
        return false;
    }

    return true;
}

void RepoWindow::initCommitHistory(const QGitRepository &repo)
{
    if (repo.isEmpty())
    {
        // This is a fresh repo. So no refs or commits in there yet.
        //! @todo Visualization of empty repo?
        return;
    }

    // Lookup the HEAD ref.
    const QGitRef headRef = repo.head();
    if (headRef.isNull())
    {
        QMessageBox::critical(0,"",tr("Couldn't find HEAD commit. Aborting ..."));
        return;
    }

    // lookup the HEAD commit
    _commitModel.setHeadCommit( repo.lookupCommit(headRef.oid()) );
    ui->tableCommits->resizeColumnsToContents();

    //! @todo For testing. All rows shall contain the "short" message format instead of the complete commit message.
    //ui->tableCommits->resizeRowsToContents();

    //! @todo Set count label as view of the commit model.
    ui->statusBar->showMessage(tr("%1 commits in repository").arg(_commitModel.rowCount()));
}

void RepoWindow::initReferences(const QGitRepository &repo)
{
    _refModel.setupRefs(repo);
}

void RepoWindow::initSubmodules(const QGitRepository &repo)
{
    //! @todo Submodules must be separated from the main repo as it should be the "root submodule".
    _submoduleModel.initialize(repo);
}
