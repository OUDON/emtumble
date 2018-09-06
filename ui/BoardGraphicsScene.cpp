#include "BoardGraphicsScene.h"
#include "../common.hpp"
#include <QPainter>

BoardGraphicsScene::BoardGraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
    current_mode = Mode::SELECT_ITEM;
}

void BoardGraphicsScene::update_graphics(BoardGUI *board)
{
    if (board == nullptr) return;
    clear();
    board->draw(this, as_image);
}

void BoardGraphicsScene::set_as_image(bool _as_image)
{
    as_image = _as_image;
}

void BoardGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF scene_pos = event->scenePos();
    QGraphicsItem *item = itemAt(scene_pos, QTransform());
    BoardGUI *board = ((MainWindow*)parent())->get_board();

    switch (current_mode) {
    case Mode::SELECT_ITEM:
        if (item != nullptr) {
            board->item_clicked(item);
            update_graphics(board);
        }
        break;

    case Mode::INSERT_ITEM:
        if (item != nullptr) {
            board->change_clicked_item(item, inserting_item);
            update_graphics(board);
        }
        break;
    }
}

void BoardGraphicsScene::set_mode(Mode mode, BoardItem::ItemType item)
{
    current_mode = mode;
    inserting_item = item;
}

void BoardGraphicsScene::export_to_image(QString file_name)
{
    QRectF r = this->itemsBoundingRect();
    QPixmap pixmap(r.width(), r.height());
    pixmap.fill(QColor(0, 0, 0, 0));
    QPainter painter(&pixmap);
    this->render(&painter);
    pixmap.save(file_name);
}
