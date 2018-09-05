#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "GUI.hpp"
#include "common.hpp"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), board(nullptr)
{
    ui->setupUi(this);

    timer_simulation_delay = new QTimer(this);
    connect(timer_simulation_delay, SIGNAL(timeout()), this, SLOT(step_board_from_timer()));

    scene = new BoardGraphicsScene(this);
    scene->set_as_image(ui->radio_button_draw_icon->isChecked());
    ui->graphics_view->setScene(scene);

    init_pallet();
    load_board(":example/example1.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::step_board()
{
    if (board == nullptr) return false;
    bool continuing = board->step();
    scene->update_graphics(board);

    /* TODO: Make more efficient */
    std::string outputs = board->get_results();
    std::string outputs_text;
    for (auto output : outputs) {
        std::string tmp;
        if (output == 'b') {
            tmp = "<font color='blue'>O</font>";
        } else if (output == 'r') {
            tmp = "<font color='red'>O</font>";
        }
        outputs_text = tmp + outputs_text;
    }
    ui->text_outputs->setText(QString::fromStdString(outputs_text));
    ui->text_outputs->setAlignment(Qt::AlignRight);

    return continuing;
}

void MainWindow::step_board_from_timer()
{
    if (!step_board()) {
        if (timer_simulation_delay->isActive()) stop_timer();
    }
}

void MainWindow::load_board(std::string fname)
{
    if (board != nullptr) delete board;
    std::vector<std::string> board_str = common::read_file_qt(fname);

    board = new BoardGUI(board_str);
    board->lever_pulled(BLUE);
    scene->update_graphics(board);
}

BoardGUI* MainWindow::get_board()
{
    return board;
}

int MainWindow::get_timer_delay() const
{
    return (ui->slider_speed->maximum() - ui->slider_speed->value() + 1 ) * 100;
}

void MainWindow::on_button_step_clicked()
{
    step_board();
}

/* Menu Bar Actions */
void MainWindow::on_action_open_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "select file");
    if (!file_name.isEmpty() && !file_name.isNull()) {
        load_board(file_name.toStdString());
    }
}

void MainWindow::on_action_toggle_outputs_bar_triggered()
{
    if (ui->text_outputs->isVisible()) {
        ui->text_outputs->setVisible(false);
        ui->action_toggle_outputs_bar->setText("Show Marble Tray");
    } else {
        ui->text_outputs->setVisible(true);
        ui->action_toggle_outputs_bar->setText("Hide Marble Tray");
    }

}

void MainWindow::on_action_clear_board_triggered()
{
    if (board != nullptr) {
        board->clear_board();
        scene->update_graphics(board);
    }
}

void MainWindow::on_button_play_clicked()
{
    if (timer_simulation_delay->isActive()) {
        stop_timer();
    } else {
        start_timer();
    }
}

void MainWindow::start_timer()
{
    if (!timer_simulation_delay->isActive()) {
        timer_simulation_delay->start(get_timer_delay());
        ui->button_play->setText("Stop");
    }
}

void MainWindow::stop_timer()
{
    if (timer_simulation_delay->isActive()) {
        timer_simulation_delay->stop();
        ui->button_play->setText("Play");
    }
}

void MainWindow::on_radio_button_draw_icon_toggled(bool checked)
{
    scene->set_as_image(ui->radio_button_draw_icon->isChecked());
    scene->update_graphics(board);
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

    layout->addWidget(create_cell_widget(QPixmap(":/img/cursol.png"), 100), 0, 0);
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
    layout->addWidget(create_cell_widget(BoardItem::SPAWN_BALL_BLUE),       6, 0);
    layout->addWidget(create_cell_widget(BoardItem::SPAWN_BALL_RED),        6, 1);
    layout->addWidget(create_cell_widget(BoardItem::LEVER_BLUE),            7, 0);
    layout->addWidget(create_cell_widget(BoardItem::LEVER_RED),             7, 1);

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
