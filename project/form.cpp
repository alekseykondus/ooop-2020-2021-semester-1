#include "form.h"
#include "ui_form.h"
#include "student.h"

#include <QFile>

form::form(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form)
{
    ui->setupUi(this);


//    this->close();

}

form::~form()
{
    delete ui;
}

void form::on_add_clicked()
{
//    Student student {ui->inpname->text(),
//                     ui->inpgroup->text(), 0};


   this->close();

   sendData();
}
