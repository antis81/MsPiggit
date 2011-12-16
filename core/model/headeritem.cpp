#include "headeritem.h"


#include <QDebug>

HeaderItem::HeaderItem(const QString & filterPrefix)
    : TreeItem("HEADER")
{
    setAcceptedChildTypes( filterPrefix );
}
