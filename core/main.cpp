#include <QtGui/QApplication>
#include <QtGui/QSplashScreen>
#include <QtGui/QBitmap>
#include <QtCore/QFile>

#ifndef QT_NO_ANIMATION
#include <QtCore/QPropertyAnimation>
#endif // QT_NO_ANIMATION

#include "ui/repowindow.h"
#include "../libs/qtuiextensions/csplashscreen.h"

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
  Main function of MsPiggit.
  */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // style
    QFile f(":/styles/main.css");
    if (f.open(QIODevice::ReadOnly))
        a.setStyleSheet(f.readAll());

    RepoWindow w;

    //show splash
    QPixmap splashPic = QPixmap(":/images/splash.png").scaledToHeight(200);
    splashPic.setMask(splashPic.mask());
    showSplash(&w, splashPic);

    return a.exec();
}
