#pragma once

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "Ball.hpp"
#include "BoardItem.hpp"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>

struct Position {
  int x, y;
  Position(int _x, int _y) : x(_x), y(_y) {}
  Position() {}
};

enum Color {
    BLUE,
    RED,
};

class Board {
protected:
    Ball *ball;
    std::vector<Ball> results;
    std::vector<std::vector<BoardItem>> cells;
    std::map<Color, Position> spawn_pos;

private:
    const std::map<BoardItem, char> item_to_symbol = {
        {BoardItem::EMPTY, ' '},
        {BoardItem::RAMP_GOING_LEFT, '<'},
        {BoardItem::RAMP_GOING_RIGHT, '>'},
        {BoardItem::BIT_POINTING_LEFT, '('},
        {BoardItem::BIT_POINTING_RIGHT, ')'},
        {BoardItem::GEAR_BIT_POINTING_LEFT, '{'},
        {BoardItem::GEAR_BIT_POINTING_RIGHT, '}'},
        {BoardItem::GEAR, '*'},
        {BoardItem::CROSS_OVER, 'x'},
        {BoardItem::INTER_CEPTER, '_'},
        {BoardItem::SPAWN_BALL_BLUE, 'B'},
        {BoardItem::SPAWN_BALL_RED, 'R'},
        {BoardItem::LEVER_BLUE, 'b'},
        {BoardItem::LEVER_RED, 'r'},
    };

    const std::map<char, BoardItem> symbol_to_item = {
        {' ', BoardItem::EMPTY},
        {'.', BoardItem::EMPTY},
        {'<', BoardItem::RAMP_GOING_LEFT},
        {'>', BoardItem::RAMP_GOING_RIGHT},
        {'(', BoardItem::BIT_POINTING_LEFT},
        {')', BoardItem::BIT_POINTING_RIGHT},
        {'{', BoardItem::GEAR_BIT_POINTING_LEFT},
        {'}', BoardItem::GEAR_BIT_POINTING_RIGHT},
        {'*', BoardItem::GEAR},
        {'x', BoardItem::CROSS_OVER},
        {'_', BoardItem::INTER_CEPTER},
        {'B', BoardItem::SPAWN_BALL_BLUE},
        {'R', BoardItem::SPAWN_BALL_RED},
        {'b', BoardItem::LEVER_BLUE},
        {'r', BoardItem::LEVER_RED},
    };

    void flip_gears_dfs(int x, int y, std::set<std::pair<int, int>> visited);
    void flip_gears(int x, int y);
    std::vector<std::string> remove_comments(std::vector<std::string> board_str);

protected:
    void flip_item(int x, int y);
    
public:
    int width, height;

    Board(int _width, int _height);
    Board(std::vector<std::string> &board_str);
    void set_item(int x, int y, BoardItem item);
    void set_items_from_strings(std::vector<std::string> board_str);
    
    void lever_pulled(Color color);
    bool add_ball(Color color);
    bool is_runnning();
    void step();
    void print() const;
    std::string get_results() const;
};

class BoardGUI : public Board {
    const std::map<BoardItem, QColor> item_to_color = {
        {BoardItem::EMPTY, Qt::white},
        {BoardItem::RAMP_GOING_LEFT, Qt::green},
        {BoardItem::RAMP_GOING_RIGHT, Qt::darkGreen},
        {BoardItem::BIT_POINTING_LEFT, Qt::blue},
        {BoardItem::BIT_POINTING_RIGHT, Qt::darkBlue},
        {BoardItem::GEAR_BIT_POINTING_LEFT, Qt::red},
        {BoardItem::GEAR_BIT_POINTING_RIGHT, Qt::darkRed},
        {BoardItem::GEAR, Qt::magenta},
        {BoardItem::CROSS_OVER, Qt::yellow},
        {BoardItem::INTER_CEPTER, Qt::gray},
        {BoardItem::SPAWN_BALL_BLUE, QColor("cornflowerblue")},
        {BoardItem::SPAWN_BALL_RED, QColor("coral")},
        {BoardItem::LEVER_BLUE, QColor("lightskyblue")},
        {BoardItem::LEVER_RED, QColor("lightpink")},
    };

    const std::map<BoardItem, QPixmap> item_to_pixmap = {
        {BoardItem::EMPTY,                   QPixmap("./img/elements/empty.png")},
        {BoardItem::RAMP_GOING_LEFT,         QPixmap("./img/elements/ramp_going_left.png")},
        {BoardItem::RAMP_GOING_RIGHT,        QPixmap("./img/elements/ramp_going_right.png")},
        {BoardItem::BIT_POINTING_LEFT,       QPixmap("./img/elements/bit_pointing_left.png")},
        {BoardItem::BIT_POINTING_RIGHT,      QPixmap("./img/elements/bit_pointing_right.png")},
        {BoardItem::GEAR_BIT_POINTING_LEFT,  QPixmap("./img/elements/gear_bit_pointing_left.png")},
        {BoardItem::GEAR_BIT_POINTING_RIGHT, QPixmap("./img/elements/gear_bit_pointing_right.png")},
        {BoardItem::GEAR,                    QPixmap("./img/elements/gear.png")},
        {BoardItem::CROSS_OVER,              QPixmap("./img/elements/crossover.png")},
        {BoardItem::INTER_CEPTER,            QPixmap("./img/elements/interceptor.png")},
        {BoardItem::SPAWN_BALL_BLUE,         QPixmap("./img/elements/spawn_ball_blue.png")},
        {BoardItem::SPAWN_BALL_RED,          QPixmap("./img/elements/spawn_ball_red.png")},
        {BoardItem::LEVER_BLUE,              QPixmap("./img/elements/empty.png")},
        {BoardItem::LEVER_RED,               QPixmap("./img/elements/empty.png")},
    };

    int zoom_rate; // %

public:
  BoardGUI(std::vector<std::string> &board_str);
  void draw(QGraphicsScene *scene, bool as_image);
  void item_clicked(QGraphicsItem *gitem);

private:
  QGraphicsItem* add_rect(QRect rect, BoardItem item, QGraphicsScene *scene, bool as_image) const;
  QRect create_rect(int x, int y, int w, int h) const;

  std::map<QGraphicsItem*, std::pair<int, int>> graphics_items;
};
