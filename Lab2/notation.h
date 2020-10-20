#ifndef NOTATION_H
#define NOTATION_H
#include <QString>

class Notation
{
private:
    QString _data;
    QString _time;
    QString _name;
    QString _text;
    int _priority;
    bool _availability = 1;

public:
    Notation();
    explicit Notation(const QString &data,
                        const QString &time,
                        const QString &name,
                        const QString &text,
                        int priority,
                        bool availability):
            _data(data), _time(time), _name(name), _text(text), _priority(priority), _availability(availability) {}
       QString data() const;
       void setData(const QString &data);
       QString time() const;
       void setTime(const QString &time);
       QString name() const;
       void setName(const QString &name);
       QString text() const;
       void setText(const QString &text);
       int priority() const;
       void setPriority(int priority);
       bool availability() const;
       void setAvailability(bool availability);
};

#endif // NOTATION_H
