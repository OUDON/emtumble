#ifndef BOARD_ITEM_H
#define BOARD_ITEM_H

#include <type_traits>

enum class BoardItem {
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

BoardItem begin(BoardItem);
BoardItem end(BoardItem);
BoardItem operator*(BoardItem item);
BoardItem operator++(BoardItem &item);

#endif
