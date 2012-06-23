#ifndef METATYPES_H
#define METATYPES_H

#include <QGit2/QGitRepository>
#include <QGit2/QGitSubmodule>
#include <QGit2/QGitRef>

// QVariant declarations
Q_DECLARE_METATYPE( LibQGit2::QGitRepository )
Q_DECLARE_METATYPE( LibQGit2::QGitSubmodule )
Q_DECLARE_METATYPE( LibQGit2::QGitRef )

#endif // METATYPES_H
