#pragma once
#include <QApplication>
#include "ui/mainwindow.h"

class GUI {
    GUI();
    ~GUI() = default;

    QApplication *app;
    MainWindow *main_window;

public:
    GUI(const GUI&) = delete;
    GUI& operator=(const GUI&) = delete;
    GUI(GUI&&) = delete;
    GUI& operator=(GUI&&) = delete;

    int start(int *argcp, char *argv[]);
    static GUI& get_instance();
};
