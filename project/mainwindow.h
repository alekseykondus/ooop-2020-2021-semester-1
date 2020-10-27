#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "task.h"
#include "student.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void load(Task *task);

private slots:
    void on_right_clicked(Task *task);
    void on_left_clicked(Task *task);
    void on_radioButton_1_clicked(Task *task);
    void on_radioButton_2_clicked(Task *task);
    void on_radioButton_3_clicked(Task *task);
    void on_radioButton_4_clicked(Task *task);

private:
    Ui::MainWindow *ui;
    void add_passed();
    void shutdown_radioButtons();
    void clear_radioButtons(Task *task);
    int create_number(Task *task);
    void show_task(Task &task);
    void load_task_from_file(Task &task, int i);
};
#endif // MAINWINDOW_H
