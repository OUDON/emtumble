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
    std::vector<std::vector<BoardItem::ItemType>> cells;
    std::map<Color, Position> spawn_pos;

private:
    const std::map<BoardItem::ItemType, char> item_to_symbol = {
        {BoardItem::EMPTY, '.'},
        {BoardItem::EMPTY_GEAR_ONLY, ' '},
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

    const std::map<char, BoardItem::ItemType> symbol_to_item = {
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
    void set_item(int x, int y, BoardItem::ItemType item);
    void set_items_from_strings(std::vector<std::string> board_str);
    
    void lever_pulled(Color color);
    bool add_ball(Color color);
    bool is_runnning();
    void step();
    void print() const;
    std::string get_results() const;
};

class BoardGUI : public Board {
    int zoom_rate; // %

public:
  BoardGUI(std::vector<std::string> &board_str);
  void draw(QGraphicsScene *scene, bool as_image);
  void item_clicked(QGraphicsItem *gitem);
  void change_clicked_item(QGraphicsItem *gitem, BoardItem::ItemType new_item_type);

private:
  QGraphicsItem* add_rect(QRect rect, BoardItem::ItemType item, QGraphicsScene *scene, bool as_image) const;
  QRect create_rect(int x, int y, int w, int h) const;
  std::pair<int, int> gitem2idx(QGraphicsItem *gitem);

  std::map<QGraphicsItem*, std::pair<int, int>> graphics_items;
};
