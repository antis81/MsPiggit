#ifndef REFERENCEMODEL_H
#define REFERENCEMODEL_H

#include <QAbstractItemModel>

#include <src/qgitref.h>
#include <model/headeritem.h>

namespace LibQGit2
{
    class QGitRepository;
}


/**
Model class for Git repository references (tags, branches, remotes).
*/
class ReferenceModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ReferenceModel(QObject *parent = 0);
    
    /**
      Get data from a @see QGitReference to edit or view a reference (branch, tag, remote).
      @todo For the beginning, only the display role should be used here. Goal is to use a QItemDelegate later on.
      */
    QVariant data(const QModelIndex& index, int role) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& index) const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    void setupRefs(const LibQGit2::QGitRepository &repo);

private:
    QList<HeaderItem>           _headers;
    QList<LibQGit2::QGitRef>    _refs;
};

#endif // REFERENCEMODEL_H
