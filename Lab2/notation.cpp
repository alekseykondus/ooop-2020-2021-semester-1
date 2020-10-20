#include "notation.h"

QString Notation::data() const
{
    return _data;
}

void Notation::setData(const QString &data)
{
    _data = data;
}

QString Notation::time() const
{
    return _time;
}

void Notation::setTime(const QString &time)
{
    _time = time;
}

QString Notation::name() const
{
    return _name;
}

void Notation::setName(const QString &name)
{
    _name = name;
}

int Notation::priority() const
{
    return _priority;
}

void Notation::setPriority(int priority)
{
    _priority = priority;
}

QString Notation::text() const
{
    return _text;
}

void Notation::setText(const QString &text)
{
    _text = text;
}

bool Notation::availability() const
{
    return _availability;
}

void Notation::setAvailability(bool availability)
{
    _availability = availability;
}

Notation::Notation()
{

}


