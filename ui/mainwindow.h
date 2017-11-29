#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_button_step_clicked();
    void on_action_open_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    void update_graphics();
};

#endif // MAINWINDOW_H
