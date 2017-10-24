#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <fstream>

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
};

class Ball {
public:
    int x, y, direction, color;

    Ball(int _x, int _y, int _direction, int _color) : 
        x(_x), y(_y), direction(_direction), color(_color) {}

    void step()
    {
        if (direction == 0) return;
        y++;
        x += direction;
    }
};

class Board {
    Ball *ball;
    std::vector<Ball> results;
    std::vector<std::vector<Item>> cells;

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
        {INTER_CEPTER, '_'}
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
        {'_', INTER_CEPTER}
    };

    void flip_gears_dfs(int x, int y, std::set<std::pair<int, int>> visited)
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

    void flip_gears(int x, int y)
    {
        std::set<std::pair<int, int>> visited;
        flip_gears_dfs(x, y, visited);
    }

public:
    int width, height;

    Board(int _width, int _height) : width(_width), height(_height)
    {
        cells.assign(height, std::vector<Item>(width));
    }

    Board(std::vector<std::string> board_str)
    {
        set_items_from_strings(board_str);
    }

    void set_item(int x, int y, Item item)
    {
        cells[y][x] = item;
    }

    void set_items_from_strings(std::vector<std::string> board_str)
    {
        int _height = board_str.size(), _width = board_str[0].size();
        cells.assign(_height, std::vector<Item>(_width));
        for (int y=0; y<_height; y++) {
            assert((int)board_str[y].size() == _width);
            for (int x=0; x<_width; x++) {
                set_item(x, y, symbol_to_item.at(board_str[y][x]));
            }
        }
        height = _height;
        width  = _width;
    }

    bool add_ball(int x, int y, Color color)
    {
        if (ball != nullptr) return false;
        int d = (color == BLUE ? 1 : -1);
        ball = new Ball(x, y, d, color);
        return true;
    }

    bool is_runnning()
    {
        if (ball == nullptr) return false;
        return (ball->direction != 0);
    }

    void step()
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

    void print() const
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

    std::string get_results() const
    {
        std::string res;
        for (auto b : results) {
            res += (b.color == BLUE ? 'b' : 'r');
        }
        return res;
    }
};

std::vector<std::string> read_file(std::string file_name)
{
    std::ifstream ifs(file_name.c_str());
    if (ifs.fail()) return std::vector<std::string>();
    std::string str;
    std::vector<std::string> res;
    while (getline(ifs, str)) {
        res.push_back(str);
        std::cerr << str << std::endl;
    }
    return res;
}

int main(int argc, char *argv[])
{    
    if (argc != 2) {
        std::cout << "Usage: emtumble filename" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filename = argv[1];
    Board board(read_file(filename));
    board.add_ball(2, -1, BLUE);
    board.print();

    while (board.is_runnning()) {
        std::cout << "---------------" << std::endl;
        board.step();
        board.print();
    }

    std::cout << "===============" << std::endl;
    std::cout << board.get_results() << std::endl;
}
