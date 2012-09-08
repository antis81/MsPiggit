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

#include <QtGui/QApplication>
#include <QtGui/QSplashScreen>
#include <QtGui/QBitmap>
#include <QtCore/QFile>

#ifndef QT_NO_ANIMATION
#include <QtCore/QPropertyAnimation>
#endif // QT_NO_ANIMATION

#include <ui/repowindow.h>
#include <../libs/qtuiextensions/csplashscreen.h>
#include <model/msptypeinfo.h>

/**
  Shows a splash screen before the program is started.

  @param w The widget to show after splash screen. 0 for no widget.
  @param splashPic The pixmap containing the splash picture.
  */
void showSplash(QWidget *w, QPixmap &splashPic)
{
    CSplashScreen *     splash = new CSplashScreen(splashPic);

#ifndef QT_NO_ANIMATION

    splash->setWindowOpacity(0.0);
    splash->show();

    QPropertyAnimation *    splashAni = new QPropertyAnimation(splash, "windowOpacity");
    splashAni->setDuration(1500);
    splashAni->setStartValue(0.0);
    splashAni->setKeyValueAt(0.2, 1.0);
    splashAni->setEndValue(1.0);

    if (w != 0)
    {
        QObject::connect(splashAni, SIGNAL(finished()), w, SLOT(show()), Qt::DirectConnection);
        QObject::connect(splashAni, SIGNAL(finished()), splash, SLOT(close()), Qt::DirectConnection);
    }

    splashAni->start(QAbstractAnimation::DeleteWhenStopped);

#else

    splash->show();
    sleep(2);

    w.show();
    splash->finish(w);

#endif // QT_NO_ANIMATION
}

/**
  Register the basic types known to MsPiggit.
  */
void registerBasicTypes()
{
    //!< @todo Outsource to some central place like main window or such
    MSPTypeInfo::instance().registerType("__HEADER__", "^(__HEADER_)");
    MSPTypeInfo::instance().registerType("__HEADER_BRANCHES__");
    MSPTypeInfo::instance().addField("__HEADER_BRANCHES__", "icon", QIcon(":/icons/branch.png"));
    MSPTypeInfo::instance().addField("__HEADER_BRANCHES__", "tooltip", QObject::tr("The active repositories branches."));

    MSPTypeInfo::instance().registerType("__HEADER_REMOTES__");
    MSPTypeInfo::instance().addField("__HEADER_REMOTES__", "icon", QIcon(":/icons/remote.png"));
    MSPTypeInfo::instance().addField("__HEADER_REMOTES__", "tooltip", QObject::tr("The active repositories remote references."));

    MSPTypeInfo::instance().registerType("__HEADER_TAGS__");
    MSPTypeInfo::instance().addField("__HEADER_TAGS__", "icon", QIcon(":/icons/tag.png"));
    MSPTypeInfo::instance().addField("__HEADER_TAGS__", "tooltip", QObject::tr("The active repositories version tags."));

    MSPTypeInfo::instance().registerType("__FOLDER__");
    MSPTypeInfo::instance().addField("__FOLDER__", "icon", QIcon(":/icons/folder.svg"));

    MSPTypeInfo::instance().registerType("repo");
    MSPTypeInfo::instance().addField("repo", "icon", QIcon(":/icons/repo.svg"));
    MSPTypeInfo::instance().registerType("subrepo");
    MSPTypeInfo::instance().addField("subrepo", "icon", QIcon(":/icons/subrepo.svg"));

    MSPTypeInfo::instance().registerType("ref_branch", "^(refs/heads/)");
    MSPTypeInfo::instance().registerType("ref_remote", "^(refs/remotes/)");
    MSPTypeInfo::instance().registerType("ref_tag", "^(refs/tags/)");
}

/**
  Main function of MsPiggit.
  */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // style
    QFile f(":/styles/main.css");
    if (f.open(QIODevice::ReadOnly))
        a.setStyleSheet(f.readAll());

    registerBasicTypes();

    RepoWindow w;

    //show splash
    QPixmap splashPic = QPixmap(":/images/splash.svg").scaledToHeight(200);
    splashPic.setMask(splashPic.mask());
    showSplash(&w, splashPic);

    return a.exec();
}
