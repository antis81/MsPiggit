#include "referencemodel.h"

ReferenceModel::ReferenceModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant ReferenceModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

Qt::ItemFlags ReferenceModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled;
}

QVariant ReferenceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

QModelIndex ReferenceModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex ReferenceModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int ReferenceModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

int ReferenceModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}
