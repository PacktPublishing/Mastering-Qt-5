#include "Album.h"

Album::Album(const QString& name) :
    mId(-1),
    mName(name)
{
}

int Album::id() const
{
    return mId;
}

void Album::setId(int id)
{
    mId = id;
}

QString Album::name() const
{
    return mName;
}

void Album::setName(const QString& name)
{
    mName = name;
}
