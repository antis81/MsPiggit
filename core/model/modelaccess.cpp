#include "modelaccess.h"

ModelAccess * ModelAccess::_instance = 0;


ModelAccess::ModelAccess()
    : _commitModel(new CommitModel())
    , _refModel(new ReferenceModel())
{
}

ModelAccess::~ModelAccess()
{
    delete _commitModel;
    delete _refModel;
}

ModelAccess &ModelAccess::instance()
{
    if (_instance == 0)
        _instance = new ModelAccess();

    return *_instance;
}

bool ModelAccess::reinitialize(const LibQGit2::QGitRepository &repo)
{
    using namespace LibQGit2;

    if (repo.isNull())
        return false;

    // initialize reference model
    _refModel->setupRefs(repo);

    //! @todo Initialize with every branches head commit, not just HEAD (!!)
    // Lookup the current repository HEAD
    QGitCommit headCommit;
    if (!repo.isEmpty())
    {
        const QGitRef headRef = repo.head();

        if (headRef.isNull())
            return false;

        headCommit = repo.lookupCommit(headRef.oid());
    }

    // lookup the HEAD commit and reinitialize the model
    _commitModel->setHeadCommit( headCommit );

    return true;
}

const CommitModel &ModelAccess::commitModel()
{
    return *_commitModel;
}

CommitModel *ModelAccess::commitModelPtr()
{
    return _commitModel;
}

const ReferenceModel &ModelAccess::refModel()
{
    return *_refModel;
}

ReferenceModel *ModelAccess::refModelPtr()
{
    return _refModel;
}
