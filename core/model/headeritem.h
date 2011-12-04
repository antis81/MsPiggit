#ifndef HEADERITEM_H
#define HEADERITEM_H

#include <QtCore/QString>
#include <QtGui/QIcon>


/**
Describes a header item to use in a Tree-, Tablemodel.
*/
class HeaderItem
{
public:
    explicit HeaderItem();
    explicit HeaderItem(const QString &text, const QIcon &icon, const QString &description = QString());

    QString text() const;
    void setText(const QString &text);

    QString description() const;
    void setDescription(const QString &description);

    QIcon icon() const;
    void setIcon(const QIcon &icon);
    
private:
    QString     _text;
    QString     _description;
    QIcon       _icon;
};

#endif // HEADERITEM_H
