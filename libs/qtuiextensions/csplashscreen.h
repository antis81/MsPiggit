#ifndef CSPLASHSCREEN__H
#define CSPLASHSCREEN__H

#include <QtGui/QFrame>

////////////////////////////////////////////////////////////////////////////
class CSplashScreen : public QFrame
{
public:
    CSplashScreen(const QPixmap& pixmap);

    void clearMessage();
    void showMessage(const QString& theMessage, int theAlignment = Qt::AlignLeft, const QColor& theColor = Qt::black);

private:
    virtual void paintEvent(QPaintEvent* pe);

    QPixmap  itsPixmap;
    QString  itsMessage;
    int   itsAlignment;
    QColor  itsColor;
};


#endif // CSPLASHSCREEN__H
