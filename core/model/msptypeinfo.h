#ifndef MSPTYPEINFO_H
#define MSPTYPEINFO_H

#include <QtCore/QHash>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QVariant>

/**
  @brief Manages central information for MsPiggit types.
  */
class MSPTypeInfo
{
public:
    typedef QMap<QString, QVariant> TypeFields;

    static MSPTypeInfo &instance();

    QVariant value(const QString &type, const QString &field) const;
    void addField(const QString &type, const QString &field, const QVariant &value);
    void registerType(const QString &type, const QString &exp = QString(), const TypeFields &fields = TypeFields());

    QString matchedType(const QString &candidate) const;

private:
    static MSPTypeInfo *                        _instance;

    QHash<QString, MSPTypeInfo::TypeFields>     _types;
    QMap<QString, QString>                      _expressions;

    MSPTypeInfo();
};

#endif // MSPTYPEINFO_H
