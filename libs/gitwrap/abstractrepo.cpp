#include "abstractrepo.h"

#include <QDir>


AbstractRepo::AbstractRepo()
{
}

AbstractRepo::~AbstractRepo()
{
}

QString AbstractRepo::path() const
{
    return _path;
}

void AbstractRepo::setPath(QString path)
{
    _path = QDir::cleanPath(path);
}
