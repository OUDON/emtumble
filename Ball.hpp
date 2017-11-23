#pragma once

class Ball {
public:
    int x, y, direction, color;

    Ball(int _x, int _y, int _direction, int _color) :
        x(_x), y(_y), direction(_direction), color(_color) {}

    void step();
};
