#pragma once
#include "Emulator.hpp"
#include "Board.hpp"

#include "ui/mainwindow.h"
#include <QApplication>
#include <QTextEdit>
#include <QtGui>
#include <QWidget>
#include <QGraphicsScene>

class GUI {
    void display();
    GUI();
    ~GUI() = default;

    QApplication *app;
    MainWindow *main_window;
    BoardGUI *board;

public:
    GUI(const GUI&) = delete;
    GUI& operator=(const GUI&) = delete;
    GUI(GUI&&) = delete;
    GUI& operator=(GUI&&) = delete;

    int start(int *argcp, char *argv[]);
    void step();
    void draw(QGraphicsScene *scene);

    static GUI& get_instance();
    void load_board(std::string fname);
};
