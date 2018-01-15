#pragma once

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "Ball.hpp"

#include <QGraphicsScene>

struct Position {
  int x, y;
  Position(int _x, int _y) : x(_x), y(_y) {}
  Position() {}
};

enum Color {
    BLUE,
    RED,
};

enum Item {
    EMPTY,
    RAMP_GOING_LEFT,
    RAMP_GOING_RIGHT,
    BIT_POINTING_LEFT,
    BIT_POINTING_RIGHT,
    GEAR_BIT_POINTING_LEFT,
    GEAR_BIT_POINTING_RIGHT,
    GEAR,
    CROSS_OVER,
    INTER_CEPTER,
    SPAWN_BALL_BLUE,
    SPAWN_BALL_RED,
    LEVER_BLUE,
    LEVER_RED,
};

class Board {
protected:
    Ball *ball;
    std::vector<Ball> results;
    std::vector<std::vector<Item>> cells;
    std::map<Color, Position> spawn_pos;

private:
    const std::map<Item, char> item_to_symbol = {
        {EMPTY, ' '},
        {RAMP_GOING_LEFT, '<'},
        {RAMP_GOING_RIGHT, '>'},
        {BIT_POINTING_LEFT, '('},
        {BIT_POINTING_RIGHT, ')'},
        {GEAR_BIT_POINTING_LEFT, '{'},
        {GEAR_BIT_POINTING_RIGHT, '}'},
        {GEAR, '*'},
        {CROSS_OVER, 'x'},
        {INTER_CEPTER, '_'},
        {SPAWN_BALL_BLUE, 'B'},
        {SPAWN_BALL_RED, 'R'},
        {LEVER_BLUE, 'b'},
        {LEVER_RED, 'r'},
    };

    const std::map<char, Item> symbol_to_item = {
        {' ', EMPTY},
        {'.', EMPTY},
        {'<', RAMP_GOING_LEFT},
        {'>', RAMP_GOING_RIGHT},
        {'(', BIT_POINTING_LEFT},
        {')', BIT_POINTING_RIGHT},
        {'{', GEAR_BIT_POINTING_LEFT},
        {'}', GEAR_BIT_POINTING_RIGHT},
        {'*', GEAR},
        {'x', CROSS_OVER},
        {'_', INTER_CEPTER},
        {'B', SPAWN_BALL_BLUE},
        {'R', SPAWN_BALL_RED},
        {'b', LEVER_BLUE},
        {'r', LEVER_RED},
    };

    void flip_gears_dfs(int x, int y, std::set<std::pair<int, int>> visited);
    void flip_gears(int x, int y);
    std::vector<std::string> remove_comments(std::vector<std::string> board_str);
    
public:
    int width, height;

    Board(int _width, int _height);
    Board(std::vector<std::string> board_str);
    void set_item(int x, int y, Item item);
    void set_items_from_strings(std::vector<std::string> board_str);
    
    void lever_pulled(Color color);
    bool add_ball(Color color);
    bool is_runnning();
    void step();
    void print() const;
    std::string get_results() const;
};

class BoardGUI : public Board {
    const std::map<Item, QColor> item_to_color = {
        {EMPTY, Qt::white},
        {RAMP_GOING_LEFT, Qt::green},
        {RAMP_GOING_RIGHT, Qt::darkGreen},
        {BIT_POINTING_LEFT, Qt::blue},
        {BIT_POINTING_RIGHT, Qt::darkBlue},
        {GEAR_BIT_POINTING_LEFT, Qt::red},
        {GEAR_BIT_POINTING_RIGHT, Qt::darkRed},
        {GEAR, Qt::magenta},
        {CROSS_OVER, Qt::yellow},
        {INTER_CEPTER, Qt::gray},
        {SPAWN_BALL_BLUE, QColor("cornflowerblue")},
        {SPAWN_BALL_RED, QColor("coral")},
        {LEVER_BLUE, QColor("lightskyblue")},
        {LEVER_RED, QColor("lightpink")},
    };

    int zoom_rate; // %

public:
  BoardGUI(std::vector<std::string> board_str);
  void draw(QGraphicsScene *scene) const;
};
