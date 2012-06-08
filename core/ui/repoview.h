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

#ifndef REPOVIEW_H
#define REPOVIEW_H

#include <QtGui/QWidget>


namespace Ui
{
    class RepoView;
}

namespace LibQGit2
{
    class QGitRepository;
}

class RepoView : public QWidget
{
    Q_OBJECT
    
public:
    explicit RepoView(QWidget *parent = 0);
    ~RepoView();

private:
    Ui::RepoView *  ui;
};

#endif // REPOVIEW_H
