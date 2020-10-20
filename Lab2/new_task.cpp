#include "new_task.h"
#include "ui_new_task.h"
#include "notation.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

new_task::new_task(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::new_task)
{
    ui->setupUi(this);
}

new_task::~new_task()
{
    delete ui;
}

void new_task::on_add_clicked()
{
    Notation notation{ui->inpdate->text(),
                     ui->inptime->text(),
                     ui->inpname->text(),
                     ui->inptext->text(),
                     ui->inppriority->value(), 1};
    QFile file{"data.txt"};
       if (!file.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
       return;

       QTextStream stream(&file);
       stream<< notation.data()<<"\n"
             << notation.time()<<"\n"
             << notation.name()<<"\n"
             << notation.text()<<"\n"
             << notation.priority()<<"\n"
             << notation.availability()<<"\n\n";

       file.close();
   this->close();
}
