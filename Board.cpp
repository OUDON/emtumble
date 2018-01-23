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
    ball = nullptr;
    cells.assign(height, std::vector<Item>(width));
}

Board::Board(std::vector<std::string> &board_str)
{
    ball = nullptr;
    set_items_from_strings(board_str);
}

void Board::set_item(int x, int y, Item item)
{
    if (item == SPAWN_BALL_BLUE || item == SPAWN_BALL_RED) {
        Color color = (item == SPAWN_BALL_BLUE ? BLUE : RED);
        if (spawn_pos.count(color)) {
            std::cerr << "WARNING: The spawn point must appear exactly once in the board for each color." << std::endl;
        }
        spawn_pos[color] = Position(x, y);
    }
    cells[y][x] = item;
}

void Board::set_items_from_strings(std::vector<std::string> board_str)
{
    spawn_pos.clear();
    board_str = remove_comments(board_str);
    int _height = board_str.size();
    if (_height == 0) return;

    int _width = board_str[0].size();
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

void Board::lever_pulled(Color color)
{
    if (ball != nullptr) {
        results.push_back(*ball);
        delete ball;
        ball = nullptr;
    }

    add_ball(color);
}

bool Board::add_ball(Color color)
{
    if (ball != nullptr) return false;
    int d = (color == BLUE ? 1 : -1);

    if (!spawn_pos.count(color)) {
        std::cerr << "WARNING: The symbol '" << "br"[color] << "' does not be appeard in the board" << std::endl;
    }

    Position pos = spawn_pos[color];
    ball = new Ball(pos.x, pos.y, d, color);
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

    Item &cell = cells[ball->y][ball->x];
    switch (cell) {
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

    case INTER_CEPTER:
        ball->direction = 0;
        break;

    case LEVER_BLUE:
        lever_pulled(BLUE);
        break;

    case LEVER_RED:
        lever_pulled(RED);
        break;

    case CROSS_OVER:
    case SPAWN_BALL_BLUE:
    case SPAWN_BALL_RED:
        // do nothing
        break;

    default:
        std::cerr << "WARNING: The ball is arrived at (" << ball->x << ", " << ball->y << "), but this cell is given no action." << std::endl;
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

BoardGUI::BoardGUI(std::vector<std::string> &board_str) : Board(board_str) {}

void BoardGUI::draw(QGraphicsScene *scene, bool as_image)
{
    QBrush green_brush(Qt::green);
    QBrush blue_brush(Qt::blue);
    QPen pen(Qt::black);
    pen.setWidth(1);

    const int CELL_WIDTH = 50, CELL_HEIGHT = 50;
    const int BALL_SIZE = 25;
    graphics_items.clear();
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            QRect rect = create_rect(x*CELL_WIDTH, y*CELL_WIDTH, CELL_WIDTH, CELL_HEIGHT);
            QGraphicsItem *gitem = add_rect(rect, cells[y][x], scene, as_image);
            graphics_items[gitem] = std::make_pair(x, y);

            if (ball != nullptr && ball->x == x && ball->y == y) {
                double cx = x * CELL_WIDTH + CELL_WIDTH/2 - BALL_SIZE/2;
                double cy = y * CELL_HEIGHT + CELL_HEIGHT/2 - BALL_SIZE/2;
                QColor color = (ball->color == BLUE ? Qt::blue : Qt::red);
                scene->addEllipse(cx, cy, BALL_SIZE, BALL_SIZE, pen, color);
            }
        }
    }
}

QGraphicsItem* BoardGUI::add_rect(QRect rect, Item item, QGraphicsScene *scene, bool as_image) const
{
    QGraphicsItem *res;
    if (as_image) {
        QPixmap pixmap = item_to_pixmap.at(item);
        pixmap = pixmap.scaled(rect.size(), Qt::KeepAspectRatioByExpanding);
        QGraphicsPixmapItem *pixmap_item = scene->addPixmap(pixmap);
        pixmap_item->setPos(rect.topLeft());
        res = pixmap_item;
    } else {
        QPen pen(Qt::black);
        pen.setWidth(1);
        res =  scene->addRect(rect, pen, QBrush(item_to_color.at(item)));
    }
    return res;
}

QRect BoardGUI::create_rect(int x, int y, int w, int h) const
{
    QRect rect = QRect(x, y, w, h);
    return rect;
}

void BoardGUI::item_clicked(QGraphicsItem *gitem)
{
    std::cerr << "Clicked: (" << graphics_items.at(gitem).first << ", " << graphics_items.at(gitem).second << ")" << std::endl;
}
