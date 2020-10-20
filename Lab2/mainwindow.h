#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "notation.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int rows;
private slots:
    void moving_to_archive(int rows);//size_t rows);
    void on_new_task_clicked();
    void on_update_clicked();

private:
    Ui::MainWindow *ui;
    //void moving_to_archive(size_t rows);
    void add_notation_to_table_notes(const Notation& notation);
    void add_notation_to_table_archive(const Notation& notation);
    void load_from_file(int i);
};
#endif // MAINWINDOW_H
