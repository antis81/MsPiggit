#include "repowindow.h"
#include "ui_repowindow.h"

#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QLabel>

#include <src/qgitrepository.h>
#include <src/qgitcommit.h>

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
    ui->treeRepoRefs->setModel(&_refModel);
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
    QString repoPath = QFileDialog::getExistingDirectory(this, tr("Open a Repository"), QDir::homePath());
    setupRepoView(repoPath);
}

void RepoWindow::setupRepoView(QString path)
{
    if (path.isEmpty() || !checkDirExists(path))
        return;

    // add .git dir to initialize repo (otherwise a bare repo is assumed)
    QDir repoDir(path);
    repoDir.setFilter(QDir::Hidden | QDir::Dirs);
    //repoDir.setSorting(Qt::AscendingOrder);
    if ( repoDir.entryList().contains(".git") )
        path += "/.git";

    // open git repository and initialize views
    QGitRepository repo;
    try
    {
        (repo.open(path));
    }
    catch (...)
    {
        QMessageBox::critical(this, tr("Unable to open repository."),
                              tr("Please check your repository path:\n%1").arg(path));
        return;
    }

    // setup the views
    initCommitHistory(repo);

    //! @todo First I want to see the history work properly, then everything else.
    initReferences(repo);
    initSubmodules(repo);
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
    //QGitRef ref = repo.data()
}

void RepoWindow::initSubmodules(const QGitRepository &repo)
{
    //! @todo Submodules must be separated from the main repo as it should be the "root submodule".
}
