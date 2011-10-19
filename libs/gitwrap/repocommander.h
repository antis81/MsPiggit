#ifndef REPOCOMMANDER_H
#define REPOCOMMANDER_H

#include <QStringList>

class AbstractRepo;


/**
Controls the execution of commands on a given repo.
*/
class RepoCommander
{
public:
    typedef QStringList Options;
    typedef QString Result;

    RepoCommander();

    Result execute(QString cmd, const AbstractRepo &repo, Options opts);
};

#endif // REPOCOMMANDER_H
