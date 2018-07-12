#ifndef BOARD_ITEM_H
#define BOARD_ITEM_H

#include <QPixmap>
#include <type_traits>
#include <string>

namespace BoardItem {
    enum ItemType {
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

    const std::map<ItemType, std::string> image_filename = {
        {EMPTY,                   "./img/elements/empty.png"},
        {RAMP_GOING_LEFT,         "./img/elements/ramp_going_left.png"},
        {RAMP_GOING_RIGHT,        "./img/elements/ramp_going_right.png"},
        {BIT_POINTING_LEFT,       "./img/elements/bit_pointing_left.png"},
        {BIT_POINTING_RIGHT,      "./img/elements/bit_pointing_right.png"},
        {GEAR_BIT_POINTING_LEFT,  "./img/elements/gear_bit_pointing_left.png"},
        {GEAR_BIT_POINTING_RIGHT, "./img/elements/gear_bit_pointing_right.png"},
        {GEAR,                    "./img/elements/gear.png"},
        {CROSS_OVER,              "./img/elements/crossover.png"},
        {INTER_CEPTER,            "./img/elements/interceptor.png"},
        {SPAWN_BALL_BLUE,         "./img/elements/spawn_ball_blue.png"},
        {SPAWN_BALL_RED,          "./img/elements/spawn_ball_red.png"},
        {LEVER_BLUE,              "./img/elements/empty.png"},
        {LEVER_RED,               "./img/elements/empty.png"},
    };

    const std::map<BoardItem::ItemType, QColor> item_to_color = {
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

    QColor color(ItemType item);
    QPixmap pixmap(ItemType item);
}

#endif
