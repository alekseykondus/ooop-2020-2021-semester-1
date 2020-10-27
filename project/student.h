#ifndef STUDENT_H
#define STUDENT_H
#include <QString>
#include <vector>

#define number_of_questions 5

class Student
{
private:
    QString _name;
    QString _group;
    QString _mark;
    int _answer_number[number_of_questions];
    bool _answers_bool[number_of_questions];

public:
    Student();
    explicit Student(const QString &name,
                     const QString &group,
                     const QString &mark):
            _name(name), _group(group), _mark(mark) {}
       QString name() const;
       void setName(const QString &name);
       QString group() const;
       void setGroup(const QString &group);
       QString mark() const;
       void setMark(const QString &mark);
       int answer_number(int number) const;
       void setAnswer_number(const int &answer_number, int number);
       bool answers_bool(int number) const;
       void setAnswers_bool(const bool &answers_bool, int number);
};

#endif // STUDENT_H
