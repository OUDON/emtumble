#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "GUI.hpp"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer_simulation_delay = new QTimer(this);
    connect(timer_simulation_delay, SIGNAL(timeout()), this, SLOT(step_board()));

    scene = new QGraphicsScene(this);
    ui->graphics_view->setScene(scene);
    GUI::get_instance().draw(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::step_board()
{
    GUI::get_instance().step();
    update_graphics();
}

void MainWindow::update_graphics()
{
    GUI::get_instance().draw(scene);
}

void MainWindow::on_button_step_clicked()
{
    step_board();
}

void MainWindow::on_action_open_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"select file");
    GUI::get_instance().load_board(file_name.toStdString());
    update_graphics();
}

void MainWindow::on_button_play_clicked()
{
    if (timer_simulation_delay->isActive()) {
        timer_simulation_delay->stop();
        ui->button_play->setText("Play");
    } else {
        timer_simulation_delay->start(500);
        ui->button_play->setText("Stop");
    }
}
