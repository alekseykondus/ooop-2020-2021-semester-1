#include "task.h"

QString Task::heading() const
{
    return _heading;
}

void Task::setHeading(const QString &heading)
{
    _heading = heading;
}

std::vector<QString> Task::assignment() const
{
    return _assignment;
}

void Task::setAssignment(const std::vector<QString> &assignment)
{
    _assignment = assignment;
}

QString Task::possible_answer_1() const
{
    return _possible_answer_1;
}

void Task::setPossible_answer_1(const QString &possible_answer_1)
{
    _possible_answer_1 = possible_answer_1;
}

QString Task::possible_answer_2() const
{
    return _possible_answer_2;
}

void Task::setPossible_answer_2(const QString &possible_answer_2)
{
    _possible_answer_2 = possible_answer_2;
}

QString Task::possible_answer_3() const
{
    return _possible_answer_3;
}

void Task::setPossible_answer_3(const QString &possible_answer_3)
{
    _possible_answer_3 = possible_answer_3;
}

QString Task::possible_answer_4() const
{
    return _possible_answer_4;
}

void Task::setPossible_answer_4(const QString &possible_answer_4)
{
    _possible_answer_4 = possible_answer_4;
}

int Task::number() const
{
    return _number;
}

void Task::setNumber(const int &number)
{
    _number = number;
}

int Task::correct() const
{
    return _correct;
}

void Task::setCorrect(const int &correct)
{
    _correct = correct;
}

Task::Task()
{

}
