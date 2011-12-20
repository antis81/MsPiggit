#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include "csplashscreen.h"

////////////////////////////////////////////////////////////////////////////
CSplashScreen::CSplashScreen(const QPixmap& thePixmap)
    : QFrame(0, Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint)
    , itsPixmap(thePixmap)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(itsPixmap.size());
    QRect scr = QApplication::desktop()->screenGeometry();
    move( scr.center() - rect().center() );
};

////////////////////////////////////////////////////////////////////////////
void CSplashScreen::clearMessage()
{
    itsMessage.clear();
    repaint();
}

////////////////////////////////////////////////////////////////////////////
void CSplashScreen::showMessage(const QString& theMessage, int theAlignment/* = Qt::AlignLeft*/, const QColor& theColor/* = Qt::black*/)
{
    itsMessage  = theMessage;
    itsAlignment = theAlignment;
    itsColor  = theColor;
    repaint();
}

////////////////////////////////////////////////////////////////////////////
void CSplashScreen::paintEvent(QPaintEvent* pe)
{
    Q_UNUSED(pe)

    QRect aTextRect(rect());
    aTextRect.setRect(aTextRect.x() + 5, aTextRect.y() + 5, aTextRect.width() - 10, aTextRect.height() - 10);

    QPainter aPainter(this);
    aPainter.drawPixmap(rect(), itsPixmap);
    aPainter.setPen(itsColor);
    aPainter.drawText(aTextRect, itsAlignment, itsMessage);
}
