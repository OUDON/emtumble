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

    init_pallet();
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

void MainWindow::init_pallet()
{
    pallet_button_group = new QButtonGroup(this);
    pallet_button_group->setExclusive(true);
    connect(pallet_button_group, SIGNAL(buttonClicked(int)),
            this, SLOT(onPalletButtonClicked(int)));

    QGridLayout *layout = ui->pallet_layout;
    layout->setSpacing(0);
    layout->setMargin(0);

    layout->addWidget(create_cell_widget(QPixmap("./img/cursol.png"), 100), 0, 0);
    layout->addWidget(create_cell_widget(BoardItem::EMPTY),                 0, 1);
    layout->addWidget(create_cell_widget(BoardItem::RAMP_GOING_LEFT),       1, 0);
    layout->addWidget(create_cell_widget(BoardItem::RAMP_GOING_RIGHT),      1, 1);
    layout->addWidget(create_cell_widget(BoardItem::CROSS_OVER),            2, 0);
    layout->addWidget(create_cell_widget(BoardItem::INTER_CEPTER),          2, 1);
    layout->addWidget(create_cell_widget(BoardItem::BIT_POINTING_LEFT),     3, 0);
    layout->addWidget(create_cell_widget(BoardItem::BIT_POINTING_RIGHT),    3, 1);
    layout->addWidget(create_cell_widget(BoardItem::GEAR_BIT_POINTING_LEFT),  4, 0);
    layout->addWidget(create_cell_widget(BoardItem::GEAR_BIT_POINTING_RIGHT), 4, 1);
    layout->addWidget(create_cell_widget(BoardItem::GEAR),                  5, 0);

    pallet_button_group->button(100)->setChecked(true);
}

QWidget* MainWindow::create_cell_widget(BoardItem::ItemType item)
{
    int id = std::underlying_type<BoardItem::ItemType>::type(item);
    return create_cell_widget(BoardItem::pixmap(item), id);
}

QWidget* MainWindow::create_cell_widget(QPixmap icon, int id)
{
    QToolButton *button = new QToolButton;
    button->setIcon(icon);
    button->setIconSize(QSize(32, 32));
    button->setCheckable(true);
    pallet_button_group->addButton(button, id);

    QGridLayout *layout = new QGridLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

void MainWindow::onPalletButtonClicked(int id)
{
    if (id == 100) {
        scene->set_mode(BoardGraphicsScene::Mode::SELECT_ITEM, BoardItem::EMPTY);
    } else {
        BoardItem::ItemType item = static_cast<BoardItem::ItemType>(id);
        scene->set_mode(BoardGraphicsScene::Mode::INSERT_ITEM, item);
    }
}
