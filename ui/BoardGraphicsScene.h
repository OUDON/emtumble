#ifndef BOARD_GRAPHICS_SCENE_H
#define BOARD_GRAPHICS_SCENE_H

#include "../Board.hpp"
#include "../BoardItem.hpp"
#include "./mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class MainWindow;
class BoardGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum class Mode { SELECT_ITEM, INSERT_ITEM };

    BoardGraphicsScene(QObject *parent = 0);
    void load_board(std::string fname);
    void set_as_image(bool _as_image);
    void step();
    void set_mode(Mode mode, BoardItem::ItemType item = BoardItem::EMPTY);
    void update_graphics(BoardGUI *board);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    bool as_image;
    Mode current_mode;
    BoardItem::ItemType inserting_item;
};

#endif
