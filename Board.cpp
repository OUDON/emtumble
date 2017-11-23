#include "Board.hpp"


void Board::flip_gears_dfs(int x, int y, std::set<std::pair<int, int>> visited)
{
    visited.insert(std::make_pair(x, y));
    Item &item = cells[y][x];
    if (item != GEAR && item != GEAR_BIT_POINTING_LEFT && item != GEAR_BIT_POINTING_RIGHT) return;

    if (item == GEAR_BIT_POINTING_LEFT) item = GEAR_BIT_POINTING_RIGHT;
    else if (item == GEAR_BIT_POINTING_RIGHT) item = GEAR_BIT_POINTING_LEFT;

    int dx[4] = {-1,  0, 1, 0};
    int dy[4] = { 0, -1, 0, 1};
    for (int i=0; i<4; i++) {
        int new_x = x + dx[i], new_y = y + dy[i];
        if (0 <= new_x && new_x < width && 0 <= new_y && new_y < height) {
            if (!visited.count(std::make_pair(new_x, new_y))) {
                flip_gears_dfs(new_x, new_y, visited);
            }
        }
    }
}

void Board::flip_gears(int x, int y)
{
    std::set<std::pair<int, int>> visited;
    flip_gears_dfs(x, y, visited);
}

std::vector<std::string> Board::remove_comments(std::vector<std::string> board_str)
{
    std::vector<std::string> res;
    for (auto row : board_str) {
        if (row.size() == 0 || row[0] == '#') continue;
        res.push_back(row);
    }
    return res;
}

Board::Board(int _width, int _height) : width(_width), height(_height)
{
    cells.assign(height, std::vector<Item>(width));
}

Board::Board(std::vector<std::string> board_str)
{
    set_items_from_strings(board_str);
}

void Board::set_item(int x, int y, Item item)
{
    cells[y][x] = item;
}

void Board::set_items_from_strings(std::vector<std::string> board_str)
{
    board_str = remove_comments(board_str);

    int _height = board_str.size(), _width = board_str[0].size();
    cells.assign(_height, std::vector<Item>(_width));
    if (_height && _width) {
        for (int y=0; y<_height; y++) {
            assert((int)board_str[y].size() == _width);
            for (int x=0; x<_width; x++) {
                set_item(x, y, symbol_to_item.at(board_str[y][x]));
            }
        }
    }
    height = _height;
    width  = _width;
}

bool Board::add_ball(int x, int y, Color color)
{
    if (ball != nullptr) return false;
    int d = (color == BLUE ? 1 : -1);
    ball = new Ball(x, y, d, color);
    return true;
}

bool Board::is_runnning()
{
    if (ball == nullptr) return false;
    return (ball->direction != 0);
}

void Board::step()
{
    if (ball == nullptr) return;
    ball->step();

    if (ball->y == height) {
        results.push_back(*ball);
        int x = ball->x;
        delete ball;
        ball = nullptr;
        if (x <= width/2) {
            add_ball(2, -1, BLUE);
        } else {
            add_ball(8, -1, RED);
        }
        return;
    }

    Item &cell = cells[ball->y][ball->x];
    switch (cell) {
    case EMPTY:
        // do nothing
        break;

    case RAMP_GOING_LEFT:
        ball->direction = -1;
        break;

    case RAMP_GOING_RIGHT:
        ball->direction = 1;
        break;

    case BIT_POINTING_LEFT:
        ball->direction = 1;
        cell = BIT_POINTING_RIGHT;
        break;

    case BIT_POINTING_RIGHT:
        ball->direction = -1;
        cell = BIT_POINTING_LEFT;
        break;

    case GEAR_BIT_POINTING_LEFT:
        ball->direction = 1;
        flip_gears(ball->x, ball->y);
        break;

    case GEAR_BIT_POINTING_RIGHT:
        ball->direction = -1;
        flip_gears(ball->x, ball->y);
        break;

    case GEAR:
        flip_gears(ball->x, ball->y);
        break;

    case CROSS_OVER:
        // do nothing
        break;

    case INTER_CEPTER:
        ball->direction = 0;
        break;
    }
}

void Board::print() const
{
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            if (ball != nullptr && ball->x == x && ball->y == y) {
                std::cout << "o";
            } else {
                std::cout << item_to_symbol.at(cells[y][x]);
            }
        }
        std::cout << std::endl;
    }
}

std::string Board::get_results() const
{
    std::string res;
    for (auto b : results) {
        res += (b.color == BLUE ? 'b' : 'r');
    }
    return res;
}
