/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Transform
*/

#pragma once

#include <cstddef>

#include "Map.hpp"

namespace emblem {
    enum Direction {
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

    struct Transform {
        Direction facing;
        size_t x;
        size_t y;

        void face(Direction direction);
        void face(const Point &point);

        void move(const Point &point);

    };
}
