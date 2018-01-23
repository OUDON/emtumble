#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "GUI.hpp"
#include "common.hpp"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer_simulation_delay = new QTimer(this);
    connect(timer_simulation_delay, SIGNAL(timeout()), this, SLOT(step_board()));

    scene = new BoardGraphicsScene(this);
    scene->set_as_image(ui->radio_button_draw_icon->isChecked());
    ui->graphics_view->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::step_board()
{
    scene->step();
}

void MainWindow::load_board(std::string fname)
{
    scene->load_board(fname);
}

int MainWindow::get_timer_delay() const
{
    return (ui->slider_speed->maximum() - ui->slider_speed->value() + 1 ) * 100;
}

void MainWindow::on_button_step_clicked()
{
    step_board();
}

void MainWindow::on_action_open_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "select file");
    load_board(file_name.toStdString());
}

void MainWindow::on_button_play_clicked()
{
    if (timer_simulation_delay->isActive()) {
        timer_simulation_delay->stop();
        ui->button_play->setText("Play");
    } else {
        timer_simulation_delay->start(get_timer_delay());
        ui->button_play->setText("Stop");
    }
}

void MainWindow::on_radio_button_draw_icon_toggled(bool checked)
{
    scene->set_as_image(ui->radio_button_draw_icon->isChecked());
}

void MainWindow::on_slider_speed_valueChanged(int value)
{
    if (timer_simulation_delay->isActive()) {
        timer_simulation_delay->setInterval(get_timer_delay());
    }
}
