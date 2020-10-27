#include "student.h"

QString Student::name() const
{
    return _name;
}

void Student::setName(const QString &name)
{
    _name = name;
}

QString Student::group() const
{
    return _group;
}

void Student::setGroup(const QString &group)
{
    _group = group;
}

QString Student::mark() const
{
    return _mark;
}

void Student::setMark(const QString &mark)
{
    _mark = mark;
}

int Student::answer_number(int number) const
{
    return _answer_number[number];
}

void Student:: setAnswer_number(const int &answer_number, int number)
{
    _answer_number[number] = answer_number;
}

bool Student::answers_bool(int number) const
{
    return _answers_bool[number];
}

void Student:: setAnswers_bool(const bool &answers_bool, int number)
{
    _answers_bool[number] = answers_bool;
}

Student::Student()
{

}
