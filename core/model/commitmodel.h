#ifndef COMMITMODEL_H
#define COMMITMODEL_H

#include <QAbstractItemModel>

#include <src/qgitcommit.h>

//namespace LibQGit2
//{
//    class QGitCommit;
//}

/**
  @brief Represents a commit history model. Currently Git only, but support for other VCS is planned for the future.
  */
class CommitModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CommitModel(QObject *parent = 0);
    ~CommitModel();

    /**
      Get data from a @see QGitCommit to edit or view a commit.
      @todo For the beginning, only the display role should be used here. Goal is to use a QItemDelegate later on.
      */
    QVariant data(const QModelIndex& index, int role) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& index) const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    /**
      Sets the commit pointing to HEAD. This is the 'root'.
      */
    void setHeadCommit(const LibQGit2::QGitCommit &commit);

private:
//    LibQGit2::QGitCommit            _headCommit;
    QList<LibQGit2::QGitCommit>     _commits;
};

#endif // COMMITMODEL_H
