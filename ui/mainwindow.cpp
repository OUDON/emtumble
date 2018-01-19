#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "GUI.hpp"
#include "common.hpp"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    board(nullptr)
{
    ui->setupUi(this);

    timer_simulation_delay = new QTimer(this);
    connect(timer_simulation_delay, SIGNAL(timeout()), this, SLOT(step_board()));

    scene = new QGraphicsScene(this);
    ui->graphics_view->setScene(scene);

    update_graphics();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::step_board()
{
    if (board == nullptr) return;
    board->step();
    update_graphics();
}

void MainWindow::load_board(std::string fname)
{
    if (board != nullptr) delete board;
    board = new BoardGUI(common::read_file(fname));
    board->lever_pulled(BLUE);
}

void MainWindow::update_graphics()
{
    if (board == nullptr) return;
    scene->clear();
    board->draw(scene, ui->radio_button_draw_icon->isChecked());
}

void MainWindow::on_button_step_clicked()
{
    step_board();
}

void MainWindow::on_action_open_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "select file");
    load_board(file_name.toStdString());
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

void MainWindow::on_radio_button_draw_icon_toggled(bool checked)
{
    update_graphics();
}
