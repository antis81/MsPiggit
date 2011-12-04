#include "headeritem.h"

HeaderItem::HeaderItem()
{
}

HeaderItem::HeaderItem(const QString &text, const QIcon &icon, const QString &description)
    : _text(text)
    , _icon(icon)
    , _description(description)
{
}

QString HeaderItem::text() const
{
    return _text;
}

void HeaderItem::setText(const QString &text)
{
    _text = text;
}

QString HeaderItem::description() const
{
    return _description;
}

void HeaderItem::setDescription(const QString &description)
{
    _description = description;
}

QIcon HeaderItem::icon() const
{
    return _icon;
}

void HeaderItem::setIcon(const QIcon &icon)
{
    _icon = icon;
}
