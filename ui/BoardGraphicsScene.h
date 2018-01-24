#ifndef BOARD_GRAPHICS_SCENE_H
#define BOARD_GRAPHICS_SCENE_H

#include "../Board.hpp"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class BoardGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    BoardGraphicsScene(QObject *parent = 0);
    void load_board(std::string fname);
    void set_as_image(bool _as_image);
    void step();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    void update_graphics();

    bool as_image;
    BoardGUI *board;
};

#endif
