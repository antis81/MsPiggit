#ifndef ABSTRACTREPOSITORY_H
#define ABSTRACTREPOSITORY_H

#include <QString>


/**
\brief Represents an abstract repository class.
*/
class AbstractRepo
{
public:
    AbstractRepo();
    ~AbstractRepo();

    QString path() const;
    void setPath(QString path);

private:
    QString     _path;
};

#endif // ABSTRACTREPOSITORY_H
