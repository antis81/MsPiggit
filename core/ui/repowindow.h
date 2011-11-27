#ifndef REPOWINDOW_H
#define REPOWINDOW_H

#include <QMainWindow>

#include <model/commitmodel.h>
#include <model/referencemodel.h>
#include <model/submodulemodel.h>

namespace LibQGit2
{
    class QGitRepository;
}

namespace Ui
{
    class RepoWindow;
}

/**
This is the main window to display a repositories content and dependencies.
*/
class RepoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RepoWindow(QWidget *parent = 0);
    ~RepoWindow();

private slots:
    /**
      Open a repository.
      */
    void openRepository();

private:
    Ui::RepoWindow *ui;

    CommitModel     _commitModel;   //!< Manages the commit history.
    ReferenceModel  _refModel;      //!< Manages the repos references
    //SubmoduleModel  _subModModel;   //!< Manages the submodules

    /**
      Setup the main menu actions.

      @todo Future work: More menu flexibility is needed. Maybe a manager using text based menu config files would do better.
      */
    void setupMainMenu();

    /**
      Setup views for a repository.
      */
    void setupRepoView(QString path);

    /**
      Check if the repository path exist and if it is a directory. If not, show a message.

      @return True if a directory exists at path. Otherwise false.
      */
    bool checkDirExists(const QString &path) const;

    /**
      Initializes the commit history view with an existing QGitRepository.
      The repository must be valid and opened before.
      */
    void initCommitHistory(const LibQGit2::QGitRepository &repo);

    /**
      Initializes the references (branches, tags, remotes) view with an existing QGitRepository.
      The repository must be valid and opened before.
      */
    void initReferences(const LibQGit2::QGitRepository &repo);

    /**
      Initializes the submodule view with an existing QGitRepository.
      The repository must be valid and opened before.
      */
    void initSubmodules(const LibQGit2::QGitRepository &repo);
};

#endif // REPOWINDOW_H
