#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Board.hpp"

#include <QMainWindow>
#include <QTimer>
#include <QWheelEvent>
#include <QButtonGroup>
#include <QToolButton>
#include "./BoardGraphicsScene.h"

namespace Ui {
class MainWindow;
}

class BoardGraphicsScene;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    BoardGUI* get_board();

private slots:
    void on_button_step_clicked();
    void on_button_play_clicked();
    void on_radio_button_draw_icon_toggled(bool checked);
    void on_slider_speed_valueChanged(int value);
    void onPalletButtonClicked(int id);
    bool step_board();
    void step_board_from_timer();

    /* Menu Bar Actions */
    void on_action_open_triggered();
    void on_action_toggle_outputs_bar_triggered();
    void on_action_clear_board_triggered();
    void on_action_export_to_image_triggered();

private:
    Ui::MainWindow *ui;
    QTimer *timer_simulation_delay;
    QButtonGroup *pallet_button_group;
    BoardGraphicsScene *scene;
    BoardGUI *board;

    void load_board(std::string fname);
    int get_timer_delay() const;
    void start_timer();
    void stop_timer();
    void init_pallet();
    QWidget* create_cell_widget(QPixmap icon, int id);
    QWidget* create_cell_widget(BoardItem::ItemType item);
};

#endif // MAINWINDOW_H
