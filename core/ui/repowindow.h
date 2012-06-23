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

#ifndef REPOWINDOW_H
#define REPOWINDOW_H

#include <QMainWindow>

#include <model/commitmodel.h>
#include <model/referencemodel.h>
#include <model/repomodel.h>

namespace LibQGit2
{
    class QGitRepository;
}

namespace Ui
{
    class RepoWindow;
}

class RepoView;


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
    void openRepository();
    void initializeRepoStatus();

private:
    Ui::RepoWindow *    ui;

    RepoView *          _repoView;  //!< pointer to the central widget
    RepoModel           _repoModel; //!< Manages the submodules

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
      Show the repository name in the window title.
      */
    void updateWindowTitle(const LibQGit2::QGitRepository &repo);
};

#endif // REPOWINDOW_H
