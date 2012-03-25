#ifndef TREEBUILDER_H
#define TREEBUILDER_H

#include <QtCore/QString>;

class TreeItem;


/**
  @brief A factory class to manage tree items in a folder like structure.
  */
class TreeBuilder
{
public:
    static TreeBuilder &instance();

    void insertItem(TreeItem *item, TreeItem *startItem
                    , QString path, const QString &filter, const QString &sep = QString("/"));

private:
    static TreeBuilder *        _instance;

    TreeBuilder();
};

#endif // TREEBUILDER_H
