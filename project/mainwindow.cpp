#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "student.h"
#include "form.h"

#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QRandomGenerator>

#define number_of_questions 5

int number = 0;
Student student;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Task *task = new Task[number_of_questions];

    form *window = new form(this);
    window->show();

    load(task);
    show_task(task[number]);

    connect(ui->radioButton_1, &QRadioButton::clicked, this,  [this, task] { this->on_radioButton_1_clicked(task); });
    connect(ui->radioButton_2, &QRadioButton::clicked, this,  [this, task] { this->on_radioButton_2_clicked(task); });
    connect(ui->radioButton_3, &QRadioButton::clicked, this,  [this, task] { this->on_radioButton_3_clicked(task); });
    connect(ui->radioButton_4, &QRadioButton::clicked, this,  [this, task] { this->on_radioButton_4_clicked(task); });

    connect(ui->left, &QCommandLinkButton::clicked, this,  [this, task] { this->on_left_clicked(task); });
    connect(ui->right, &QCommandLinkButton::clicked, this,  [this, task] { this->on_right_clicked(task); });

//    connect(window, SIGNAL(sendData()), this, SLOT(load(show_task(task[0]))));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_task(Task &task)
{
    QString str = "Задание № ";
    char a = (char)number + '0'+ 1;
    ui->label->setText(str + a);
    ui->question->setText(task.heading());
    for (auto const &element: task.assignment())
        ui->task->append(element);
    ui->radioButton_1->setText(task.possible_answer_1());
    ui->radioButton_2->setText(task.possible_answer_2());
    ui->radioButton_3->setText(task.possible_answer_3());
    ui->radioButton_4->setText(task.possible_answer_4());

    int result = 0;
    for (int j = 0; j < number_of_questions; j++)
        if (student.answers_bool(j) == true)
            result++;
    str = "Result:  ";
    a = (char)result + '0';
    ui->result->setText(str + a);
    QColor color(255, 127, 50);
    ui->result->setStyleSheet(QString("color: %1").arg(color.name()));
}

int MainWindow::create_number(Task *task)
{
    QDateTime DTime = QDateTime::currentDateTime();
    int i;
    bool b = false;
    while(b == false)
    {
        b = true;
        if ( DTime.time().msec() != 0 && DTime.time().second() != 0)
             i = DTime.time().msec()*DTime.time().second()*QRandomGenerator::global()->generate()%7;
        else
            i = QRandomGenerator::global()->generate()%7;
        for (int j = 0; j < number_of_questions; j++)
            if (i == task[j].number())
                b = false;
    }
    return i;
}

void MainWindow::load(Task *task)
{
    for (int i = 0; i < number_of_questions; i++)
        load_task_from_file(task[i], create_number(task));
}

void MainWindow::load_task_from_file(Task &task, int i)
{
    std::vector<QString> assignment;
    task.setNumber(i);

    QFile file{"data.txt"};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString line;
    QTextStream in(&file);
    for (int j = 0; j < i && !in.atEnd(); j++)
    {
        QString line = in.readLine();
        while(line != "-------------------------")
            line = in.readLine();
    }

    line  = in.readLine();
    task.setHeading(line);
    line = in.readLine();

    line = in.readLine();
    while(line != "------- 1" && line != "------- 2" && line != "------- 3" && line != "------- 4")
    {
        assignment.push_back(line);
        line = in.readLine();
    }
    task.setAssignment(assignment);
    task.setCorrect(line[line.size()-1].unicode()-'0');

    line = in.readLine();
    task.setPossible_answer_1(line);
    line = in.readLine();
    task.setPossible_answer_2(line);
    line = in.readLine();
    task.setPossible_answer_3(line);
    line = in.readLine();
    task.setPossible_answer_4(line);

    file.close();
}

void MainWindow::clear_radioButtons(Task *task)
{
    ui->task->clear();
    ui->radioButton_1->setStyleSheet("background-color: ");
    ui->radioButton_2->setStyleSheet("background-color: ");
    ui->radioButton_3->setStyleSheet("background-color: ");
    ui->radioButton_4->setStyleSheet("background-color: ");
    connect(ui->radioButton_1, &QRadioButton::clicked, this,  [this, task] { this->on_radioButton_1_clicked(task); });
    connect(ui->radioButton_2, &QRadioButton::clicked, this,  [this, task] { this->on_radioButton_2_clicked(task); });
    connect(ui->radioButton_3, &QRadioButton::clicked, this,  [this, task] { this->on_radioButton_3_clicked(task); });
    connect(ui->radioButton_4, &QRadioButton::clicked, this,  [this, task] { this->on_radioButton_4_clicked(task); });

    ui->radioButton_1->setCheckable(true);
    ui->radioButton_2->setCheckable(true);
    ui->radioButton_3->setCheckable(true);
    ui->radioButton_4->setCheckable(true);

}

void MainWindow::add_passed()
{
    if (student.answer_number(number) == 1)
     {
         if (student.answers_bool(number) == true)
             ui->radioButton_1->setStyleSheet("background-color: green");
         else
             ui->radioButton_1->setStyleSheet("background-color: red");
     }
     else if (student.answer_number(number) == 2)
     {
         if (student.answers_bool(number) == true)
             ui->radioButton_2->setStyleSheet("background-color: green");
         else
             ui->radioButton_2->setStyleSheet("background-color: red");
     }
     else if (student.answer_number(number) == 3)
     {
         if (student.answers_bool(number) == true)
             ui->radioButton_3->setStyleSheet("background-color: green");

         else
             ui->radioButton_3->setStyleSheet("background-color: red");
     }
     else if (student.answer_number(number) == 4)
     {
         if (student.answers_bool(number) == true)
             ui->radioButton_4->setStyleSheet("background-color: green");
         else
             ui->radioButton_4->setStyleSheet("background-color: red");
     }
   shutdown_radioButtons();
}

void MainWindow::on_right_clicked(Task *task)
{
    if (number < number_of_questions-1)
    {
        number++;
        clear_radioButtons(task);
        show_task(task[number]);

        if ((student.answer_number(number) == 1 || student.answer_number(number) == 2 || student.answer_number(number) == 3 || student.answer_number(number) == 4))
            add_passed();
    }
}

void MainWindow::shutdown_radioButtons()
{
    ui->radioButton_1->disconnect();
    ui->radioButton_2->disconnect();
    ui->radioButton_3->disconnect();
    ui->radioButton_4->disconnect();

    ui->radioButton_1->setCheckable(false);
    ui->radioButton_2->setCheckable(false);
    ui->radioButton_3->setCheckable(false);
    ui->radioButton_4->setCheckable(false);
}

void MainWindow::on_left_clicked(Task *task)
{
    if (number > 0)
    {
        number--;
        clear_radioButtons(task);
        show_task(task[number]);
     if ((student.answer_number(number) == 1 || student.answer_number(number) == 2 || student.answer_number(number) == 3 || student.answer_number(number) == 4))
        add_passed();
    }
}

void MainWindow::on_radioButton_1_clicked(Task *task)
{
    student.setAnswer_number(1, number);
    if (task[number].correct() == 1)
    {
        student.setAnswers_bool(true, number);
        ui->radioButton_1->setStyleSheet("background-color: green");
    }
    else
    {
        student.setAnswers_bool(false, number);
        ui->radioButton_1->setStyleSheet("background-color: red");
    }
    shutdown_radioButtons();
}

void MainWindow::on_radioButton_2_clicked(Task *task)
{
    student.setAnswer_number(2, number);
    if (task[number].correct() == 2)
    {
        student.setAnswers_bool(true, number);
        ui->radioButton_2->setStyleSheet("background-color: green");
    }
    else
    {
        student.setAnswers_bool(false, number);
        ui->radioButton_2->setStyleSheet("background-color: red");
    }
    shutdown_radioButtons();
}

void MainWindow::on_radioButton_3_clicked(Task *task)
{
    student.setAnswer_number(3, number);
    if (task[number].correct() == 3)
    {
        student.setAnswers_bool(true, number);
        ui->radioButton_3->setStyleSheet("background-color: green");
    }
    else
    {
        student.setAnswers_bool(false, number);
        ui->radioButton_3->setStyleSheet("background-color: red");
    }
    shutdown_radioButtons();
}

void MainWindow::on_radioButton_4_clicked(Task *task)
{
    student.setAnswer_number(4, number);
    if (task[number].correct() == 4)
    {
        student.setAnswers_bool(true, number);
        ui->radioButton_4->setStyleSheet("background-color: green");
    }
    else
    {
        student.setAnswers_bool(false, number);
        ui->radioButton_4->setStyleSheet("background-color: red");
    }
    shutdown_radioButtons();
}
