#ifndef TREEITEM_H
#define TREEITEM_H

#include <QtCore/QStringList>
#include <QtGui/QIcon>


class TreeItem
{
public:
    explicit TreeItem(const QString &name);
    virtual ~TreeItem();

    const QString &acceptedChildTypes() const;
    void setAcceptedChildTypes(const QString &types);

    QString pathSeparator() const;
    void setPathSeparator(const QString &sep);

    QString name(bool fullName = false) const;
    void setName(const QString &name);

    QString text() const;
    void setText(const QString &text);

    QString description() const;
    void setDescription(const QString &description);

    QIcon icon() const;
    void setIcon(const QIcon &icon);

    TreeItem *parent() const;
    void setParent(TreeItem *newParent);
    const QList<TreeItem *> &children() const;

    virtual TreeItem *appendChild(const QString &path);

    void removeChild(TreeItem * child);

    int row();
    int indexOf(const QString &name) const;

protected:
    TreeItem * appendChild(TreeItem * child);

private:
    TreeItem *          _parent;
    QList<TreeItem *>   _children;
    QString             _acceptedChildTypes;
    QString             _pathSeparator; //!< regular expression string to separate the item into a path structure

    QString     _text;
    QString     _description;
    QIcon       _icon;
    QString     _name; //!< the items name is used as it's id it can be part of a path.
    //QString     _fullName;

    TreeItem *seperatePath(QString name);
};

#endif // TREEITEM_H
