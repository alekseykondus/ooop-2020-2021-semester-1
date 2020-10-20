#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "new_task.h"
#include "notation.h"

#include <QFile>
#include <QTextStream>
#include <QTableWidgetItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    load_from_file(1);
    load_from_file(2);

    QTableWidgetItem* item = new QTableWidgetItem("Дата");
    ui->tbwNotation_Notes->setHorizontalHeaderItem(0, item);

    item = new QTableWidgetItem("Время");
    ui->tbwNotation_Notes->setHorizontalHeaderItem(1, item);

    item = new QTableWidgetItem("Название");
    ui->tbwNotation_Notes->setHorizontalHeaderItem(2, item);

    item = new QTableWidgetItem("Информация");
    ui->tbwNotation_Notes->setHorizontalHeaderItem(3, item);

    item = new QTableWidgetItem("Приоритет");
    ui->tbwNotation_Notes->setHorizontalHeaderItem(4, item);

    item = new QTableWidgetItem("В архив");
    ui->tbwNotation_Notes->setHorizontalHeaderItem(5, item);

    item = new QTableWidgetItem("Дата");
    ui->tbwNotation_Archive->setHorizontalHeaderItem(0, item);

    item = new QTableWidgetItem("Время");
    ui->tbwNotation_Archive->setHorizontalHeaderItem(1, item);

    item = new QTableWidgetItem("Название");
    ui->tbwNotation_Archive->setHorizontalHeaderItem(2, item);

    item = new QTableWidgetItem("Информация");
    ui->tbwNotation_Archive->setHorizontalHeaderItem(3, item);

    item = new QTableWidgetItem("Приоритет");
    ui->tbwNotation_Archive->setHorizontalHeaderItem(4, item);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_new_task_clicked()
{
   new_task *window = new new_task;
   window->show();
}

void MainWindow::add_notation_to_table_notes(const Notation &notation)
{
    const int rows = ui->tbwNotation_Notes->rowCount();
    ui->tbwNotation_Notes->setRowCount(rows+1);

    ui->tbwNotation_Notes->setColumnCount(6);

    QTableWidgetItem* item = new QTableWidgetItem(notation.data());
    ui->tbwNotation_Notes->setItem(rows, 0, item);

    item = new QTableWidgetItem(notation.time());
    ui->tbwNotation_Notes->setItem(rows, 1, item);

    item = new QTableWidgetItem(notation.name());
    ui->tbwNotation_Notes->setItem(rows, 2, item);

    item = new QTableWidgetItem(notation.text());
    ui->tbwNotation_Notes->setItem(rows, 3, item);

    item = new QTableWidgetItem(QString::number(notation.priority()));
    ui->tbwNotation_Notes->setItem(rows, 4, item);

    QPushButton *button = new QPushButton();

    button->setText("Del");
    ui->tbwNotation_Notes->setCellWidget(rows, 5, button);

    QObject::connect(button, SIGNAL(clicked()), this, SLOT(moving_to_archive())); //Работает
    //QObject::connect(button, SIGNAL(clicked()), this, SLOT(moving_to_archive(rows+1))); //Не работает
}


//реализация переноса записи в архив
//void MainWindow::moving_to_archive(int rows)//Не работает
void MainWindow::moving_to_archive() //Работает
{
    qDebug() << true;
    QFile file{"data.txt"};
    QFile file2{"data_copy.txt"};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    if (!file2.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
        return;
    QTextStream in(&file);

    QTextStream stream(&file2);
    size_t i = 1;
    int current_field = 0;
    Notation current_notation;
    while (!in.atEnd())
    {
       QString line = in.readLine();
       switch (current_field) {
       case 0:
           current_notation.setData(line);
           break;
       case 1:
           current_notation.setTime(line);
           break;
       case 2:
           current_notation.setName(line);
           break;
       case 3:
           current_notation.setText(line); //нужно будет изменять line на что-то
           break;
       case 4:
           current_notation.setPriority(line.toInt());
           break;
       case 5:
            current_notation.setAvailability(line.toInt());
           break;
       }

       switch (current_field) {
       case 0:
           stream<< current_notation.data()<<"\n";
           break;
       case 1:
           stream<< current_notation.time()<<"\n";
           break;
       case 2:
           stream<< current_notation.name()<<"\n";
           break;
       case 3:
           stream<< current_notation.text()<<"\n";
           break;
       case 4:
           stream<< current_notation.priority()<<"\n";
           break;
       case 5:
            if (i == rows) //в этой строчке определаю, какую именно запись нужно перенести в архив
                stream<< 0 <<"\n\n";
            else
                stream<< current_notation.availability()<<"\n\n";
           break;
       default:
           current_field = -1;
           i++;
           break;
       }
        current_field++;
    }
    file.close();
    file2.close();

    remove("data.txt");
    rename("data_copy.txt", "data.txt");
}

void MainWindow::add_notation_to_table_archive(const Notation &notation)
{
    int rows = ui->tbwNotation_Archive->rowCount();
    ui->tbwNotation_Archive->setRowCount(rows+1);

    ui->tbwNotation_Archive->setColumnCount(5);

    QTableWidgetItem* item = new QTableWidgetItem(notation.data());
    ui->tbwNotation_Archive->setItem(rows, 0, item);

    item = new QTableWidgetItem(notation.time());
    ui->tbwNotation_Archive->setItem(rows, 1, item);

    item = new QTableWidgetItem(notation.name());
    ui->tbwNotation_Archive->setItem(rows, 2, item);

    item = new QTableWidgetItem(notation.text());
    ui->tbwNotation_Archive->setItem(rows, 3, item);

    item = new QTableWidgetItem(QString::number(notation.priority()));
    ui->tbwNotation_Archive->setItem(rows, 4, item);
}

void MainWindow::load_from_file(int i)
{
    QFile file{"data.txt"};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
  if (i == 1) {
      ui->tbwNotation_Notes->clearContents();
      ui->tbwNotation_Notes->setRowCount(0);
  }
  else{
      ui->tbwNotation_Archive->clearContents();
      ui->tbwNotation_Archive->setRowCount(0);
  }
    QTextStream in(&file);
    int current_field = 0;
    Notation current_notation;
    while (!in.atEnd())
    {
       QString line = in.readLine();
       switch (current_field) {
       case 0:
           current_notation.setData(line);
           break;
       case 1:
           current_notation.setTime(line);
           break;
       case 2:
           current_notation.setName(line);
           break;
       case 3:
           current_notation.setText(line); //нужно будет изменять line на что-то
           break;
       case 4:
           current_notation.setPriority(line.toInt());
           break;
       case 5:
            current_notation.setAvailability(line.toInt());
           break;
       case 6:
           current_field = -1;
           if (i == 1 && current_notation.availability())
               add_notation_to_table_notes(current_notation);
           else if (i == 2 && !current_notation.availability())
               add_notation_to_table_archive(current_notation);
           break;
       }
       current_field++;
    }
    file.close();
}

void MainWindow::on_update_clicked()
{
     load_from_file(1);
     load_from_file(2);
}
