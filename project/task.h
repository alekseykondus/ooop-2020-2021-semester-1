#ifndef TASK_H
#define TASK_H
#include <QString>
#include <vector>
class Task
{
private:
    QString _heading;
    std::vector<QString> _assignment;
    QString _possible_answer_1;
    QString _possible_answer_2;
    QString _possible_answer_3;
    QString _possible_answer_4;
    int _number = -1;
    int _correct;

public:
    Task();
       QString heading() const;
       void setHeading(const QString &heading);
       std::vector<QString> assignment() const;
       void setAssignment(const std::vector<QString> &assignment);
       QString possible_answer_1() const;
       void setPossible_answer_1(const QString &possible_answer_1);
       QString possible_answer_2() const;
       void setPossible_answer_2(const QString &possible_answer_2);
       QString possible_answer_3() const;
       void setPossible_answer_3(const QString &possible_answer_3);
       QString possible_answer_4() const;
       void setPossible_answer_4(const QString &possible_answer_4);
       int number() const;
       void setNumber(const int &correct);
       int correct() const;
       void setCorrect(const int &correct);
};

#endif // TASK_H
