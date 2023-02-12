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
        Direction facing = NORTH;
        int64_t x = 0;
        int64_t y = 0;

        void face(Direction direction);
        void face(const Point &point);

        void move(const Point &point);

    };
}
