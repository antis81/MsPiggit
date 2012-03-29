#include "msptypeinfo.h"

#include <QtCore/QRegExp>


MSPTypeInfo * MSPTypeInfo::_instance = 0;

MSPTypeInfo::MSPTypeInfo()
{
}

QString MSPTypeInfo::matchedType(const QString &candidate) const
{
    QMap<QString, QString>::const_iterator it = _expressions.constBegin();
    while ( it != _expressions.constEnd() )
    {
        // candidate is the type?
        if (it.value() == candidate)
            return candidate;

        // candidate matches the regex for the type?
        QRegExp exp(it.key());
        exp.setMinimal(true);
        if (exp.indexIn(candidate) >= 0)
            return it.value();

        it++;
    }

    // string does not match any type
    return QString();
}

MSPTypeInfo &MSPTypeInfo::instance()
{
    if (_instance == 0)
        _instance = new MSPTypeInfo();

    return *_instance;
}

/**
  Reads a field of an existing type.

  @param type the type to read the field from
  @param field the field name
  @return the field value or an empty QVariant if the field was not found
  */
QVariant MSPTypeInfo::value(const QString &type, const QString &field) const
{
    if (!_types.contains(type))
        return QVariant();

    const MSPTypeInfo::TypeFields &   fields = _types.value(type);

    return fields.value(field);
}

/**
  Sets a named field for an existing type, that can be used to store additional information.

  @param type the type to add the field to
  @param the field name
  @param value a QVariant value constant
  */
void MSPTypeInfo::addField(const QString &type, const QString &field, const QVariant &value)
{
    if (!_types.contains(type))
        return;

    MSPTypeInfo::TypeFields   & fields = _types[type];
    fields.insert(field, value);
}

/**
  Adds a type entry to the list of available types. The type must be a unique regular expression string.

  @param type an application wide unique type name
  @param exp a regular expression string to match the type
  @param fields optional fields to store information to the type
  */
void MSPTypeInfo::registerType(const QString &type, const QString &exp, const TypeFields &fields)
{
    if (type.isEmpty() || _types.contains(type))
        return;

    _types.insert(type, fields);

    if (!exp.isEmpty())
        _expressions.insert(exp, type);
}
