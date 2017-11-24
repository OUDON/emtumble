#pragma once
#include "Emulator.hpp"
#include "Board.hpp"

#include <QApplication>
#include <QTextEdit>
#include <QtGui>
#include <QWidget>

class GUI {
    void display();
    GUI();
    ~GUI() = default;
    Board *board;

public:
    GUI(const GUI&) = delete;
    GUI& operator=(const GUI&) = delete;
    GUI(GUI&&) = delete;
    GUI& operator=(GUI&&) = delete;

    int start(int *argcp, char *argv[]);

    static GUI& get_instance();
    void load_board(std::string fname);
};

class Paint : public QWidget {
    // Q_OBJECT
public:
protected:
        void paintEvent(QPaintEvent *event);
signals:
public slots:
};
