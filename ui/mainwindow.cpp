#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "GUI.hpp"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphics_view->setScene(scene);
    GUI::get_instance().draw(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_graphics()
{
    GUI::get_instance().draw(scene);
}

void MainWindow::on_button_step_clicked()
{
    GUI::get_instance().step();
    update_graphics();
}

void MainWindow::on_action_open_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"select file");
    GUI::get_instance().load_board(file_name.toStdString());
    update_graphics();
}
