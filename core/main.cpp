#include <QtGui/QApplication>
#include <QtGui/QSplashScreen>
#include <QtGui/QBitmap>

#ifndef QT_NO_ANIMATION
#include <QtCore/QPropertyAnimation>
#endif // QT_NO_ANIMATION

#include "ui/repowindow.h"
#include "../libs/qtuiextensions/csplashscreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap             splashPic = QPixmap(":/images/splash.png").scaledToHeight(200);
    splashPic.setMask(splashPic.mask());
    CSplashScreen *     splash = new CSplashScreen(splashPic);

#ifndef QT_NO_ANIMATION

    splash->setWindowOpacity(0.0);
    splash->show();

    QPropertyAnimation *    splashAni = new QPropertyAnimation(splash, "windowOpacity");
    splashAni->setDuration(3000);
    splashAni->setStartValue(0.0);
    splashAni->setKeyValueAt(0.2, 1.0);
    splashAni->setEndValue(1.0);

    RepoWindow w;
    QObject::connect(splashAni, SIGNAL(finished()), &w, SLOT(show()), Qt::DirectConnection);
    QObject::connect(splashAni, SIGNAL(finished()), splash, SLOT(close()), Qt::DirectConnection);

    splashAni->start(QAbstractAnimation::DeleteWhenStopped);

#else

    RepoWindow w;

    splash->show();
    sleep(2);

    w.show();
    splash->finish(&w);

#endif // QT_NO_ANIMATION

    return a.exec();
}
