#include "repowindow.h"
#include "ui_repowindow.h"

#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

#include <src/qgitrepository.h>
#include <src/qgitcommit.h>

#include <model/commitmodel.h>

using namespace LibQGit2;


RepoWindow::RepoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RepoWindow)
{
    ui->setupUi(this);

    setupMainMenu();
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
    if (repo.open(path) != 0)
    {
        QMessageBox::critical(this, tr("Unable to open repository."),
                              tr("Please check your repository path:\n%1").arg(path));
        return;
    }

    // setup the views
    initCommitHistory(repo);

    //! @todo First I want to see the history work properly, then everything else.
    //initReferences(repo);
    //initSubmodules(repo)
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
    QGitOId oid = repo.head().oid();
    QMessageBox::information(0,"",tr("And the HEAD is ...\n%1").arg(QString(oid.format())));
    if (!oid.isValid())
    {
        //! @todo HEAD not found. Ask for repository initialization "git init".
        QMessageBox::information(0,"",tr("Couldn't find HEAD commit. Aborting ..."));
        return;
    }

    // lookup the HEAD commit
    QGitCommit commit( repo.lookupCommit(oid) );
    QMessageBox::information(0,"",tr("The committer said:\n%1").arg(commit.message()));
    ui->tableCommits->setModel(new CommitModel(commit, 0));
}
