#ifndef FORM_H
#define FORM_H

#include <QMainWindow>
#include "student.h"

namespace Ui {
class form;
}

class form : public QMainWindow
{
    Q_OBJECT

public:
    explicit form(QWidget *parent = nullptr);
    ~form();

signals:
   void sendData();

private slots:
    void on_add_clicked();

private:
    Ui::form *ui;
};

#endif // FORM_H
