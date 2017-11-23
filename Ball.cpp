#include "Ball.hpp"

void Ball::step()
{
    if (direction == 0) return;
    y++;
    x += direction;
}
