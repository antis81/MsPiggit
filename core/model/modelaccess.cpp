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
    if (repo.isNull())
        return false;

    // initialize reference model
    _refModel->setupRefs(repo);

    // initialize the commit model
    _commitModel->initialize( repo );

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
