#ifndef NEW_TASK_H
#define NEW_TASK_H

#include <QMainWindow>
#include <QApplication>

namespace Ui {
class new_task;
}

class new_task : public QMainWindow
{
    Q_OBJECT

public:
    explicit new_task(QWidget *parent = nullptr);
    ~new_task();

private slots:
    void on_add_clicked();

private:
    Ui::new_task *ui;
};

#endif // NEW_TASK_H
