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

using namespace LibQGit2;


RepoWindow::RepoWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RepoWindow)
{
    ui->setupUi(this);

    setupMainMenu();

    // setup the models
    ui->tableCommits->setModel(&_commitModel);
    ui->tableCommits->horizontalHeader()->setMovable(true);
    ui->treeRepoRefs->setModel(&_refModel);
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
    QGitRepository repo;
    try
    {
        repo.discoverAndOpen(path);
        updateWindowTitle( repo );
    }
    catch (LibQGit2::QGitException e)
    {
        QMessageBox::critical( this, tr("Unable to open repository."), e.message() );
        return;
    }

    // setup the views
    initCommitHistory(repo);
    initReferences(repo);
    initSubmodules(repo);
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
