#ifndef MODELACCESS_H
#define MODELACCESS_H

#include <model/commitmodel.h>
#include <model/referencemodel.h>


/**
  @brief Provides access to application central data models.
*/
class ModelAccess
{
public:
    static ModelAccess &instance();

    bool reinitialize(const LibQGit2::QGitRepository &repo);

    const CommitModel &commitModel();
    CommitModel *commitModelPtr();

    const ReferenceModel &refModel();
    ReferenceModel *refModelPtr();

//    void initCommitModel(const LibQGit2::QGitRepository &repo);
//    void initRefModel(const LibQGit2::QGitRepository &repo);

private:
    static ModelAccess *        _instance;

    CommitModel *        _commitModel;
    ReferenceModel *     _refModel;

    ModelAccess();
    ~ModelAccess();
};

#endif // MODELACCESS_H
