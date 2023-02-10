/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Transform
*/

#include "component/Transform.hpp"

void emblem::Transform::face(Direction direction) {
    facing = direction;
}

void emblem::Transform::face(const Point &point) {
    if (point.x > x)
        facing = EAST;
    else if (point.x < x)
        facing = WEST;
    else if (point.y > y)
        facing = SOUTH;
    else if (point.y < y)
        facing = NORTH;
}


void emblem::Transform::move(const emblem::Point &point) {
    x = point.x;
    y = point.y;
}
