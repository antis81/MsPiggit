#include "treebuilder.h"

#include <model/treeitem.h>


TreeBuilder * TreeBuilder::_instance = 0;


TreeBuilder::TreeBuilder()
{
}

TreeBuilder &TreeBuilder::instance()
{
    if (_instance == 0)
        _instance = new TreeBuilder();

    return *_instance;
}

void TreeBuilder::insertItem(TreeItem *item, TreeItem *startItem, QString path, const QString &filter, const QString &sep)
{
    path.remove(QRegExp(filter));
    QStringList subPaths = path.split(QRegExp(sep));

    if (subPaths.isEmpty())
        return;

    // subdivide folders
    TreeItem *tmpItem = startItem;
    while ( subPaths.count() > 1 )
    {
        QString s = subPaths.takeFirst();

        // check for existing folder item
        TreeItem *  folderItem = tmpItem->findTextItem(s);
        if (folderItem == 0)
        {
            // add new folder item
            folderItem = new TreeItem("__FOLDER__");
            folderItem->setText( s );
            tmpItem->appendChild(folderItem);
        }

        // assign folder item as new parent
        tmpItem = folderItem;
    }

    // add the item to the last folder item
    item->setText(subPaths.takeFirst());
    tmpItem->appendChild(item);
}
