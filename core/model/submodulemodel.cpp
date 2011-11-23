#include "submodulemodel.h"

SubmoduleModel::SubmoduleModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant SubmoduleModel::data(const QModelIndex &index, int role) const
{
}

Qt::ItemFlags SubmoduleModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled;
}

QVariant SubmoduleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

QModelIndex SubmoduleModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex SubmoduleModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int SubmoduleModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

int SubmoduleModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}
