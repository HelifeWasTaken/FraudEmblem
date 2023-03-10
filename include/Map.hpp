/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Map
*/

#pragma once

#include <cstddef>
#include <cstdint>
#include <climits>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <algorithm>

namespace emblem {
    struct Point {
        int64_t x = 0;
        int64_t y = 0;

        bool operator==(const Point &other) const {
            return x == other.x && y == other.y;
        }
    };

    static const size_t MASK_CELL_TYPE = 0x0f;
    static const size_t EXCLUDE_MASK_CELL_TYPE = ~MASK_CELL_TYPE;

    static const size_t MASK_CELL_ENTITY_TYPE = 0xf0;
    static const size_t EXCLUDE_MASK_CELL_ENTITY_TYPE = ~MASK_CELL_ENTITY_TYPE;

    enum CellType {
        IGNORE = -1,
        EMPTY,
        WALL,
        INTERACT,
        ENTITY
    };

    enum EntityType {
        HERO,
        VILLAIN,
        NEUTRAL
    };

    struct Cell {
        Cell() : Cell(EMPTY) {}

        Cell(uint8_t type) {
            setCellType(type);
        }

        Cell &setCellType(uint8_t type) {
            __data &= EXCLUDE_MASK_CELL_TYPE;
            __data |= type & 0xf;
            return *this;
        }

        Cell &setEntityType(uint8_t type) {
            __data &= EXCLUDE_MASK_CELL_ENTITY_TYPE;
            __data |= (type & 0xf) << 4;
            return *this;
        }

        CellType getCellType() const {
            return static_cast<CellType>(__data & MASK_CELL_TYPE);
        }

        EntityType getEntityType() const {
            return static_cast<EntityType>((__data & MASK_CELL_ENTITY_TYPE) >> 4);
        }

        bool operator==(const Cell &other) const {
            return __data == other.__data;
        }

        private:
            size_t __data = 0;
    };

    using Area = std::unordered_map<Point, CellType>;
    using Path = std::vector<Point>;

    class Map {
        size_t __width;
        size_t __height;

        std::vector<std::vector<Cell>> __map;

        bool __excludeWall = false;
        Point __origin;
        Cell __ignore;

        public:
            Map(const size_t &width, const size_t &height);
            ~Map() = default;

            void setWall(const size_t &x, const size_t &y);
            void setEmpty(const size_t &x, const size_t &y);
            void setEntity(const size_t &x, const size_t &y, const uint8_t &type);

            void setCell(const size_t &x, const size_t &y, const Cell &value);

            bool isWall(const size_t &x, const size_t &y) const;
            bool isEmpty(const size_t &x, const size_t &y) const;
            bool isEntity(const size_t &x, const size_t &y) const;

            bool isHero(const size_t &x, const size_t &y) const;
            bool isVillain(const size_t &x, const size_t &y) const;
            bool isNeutral(const size_t &x, const size_t &y) const;
            bool isIgnore(const size_t &x, const size_t &y) const;

            Map &setIgnore(const Cell &cell);

            Map &excludeWall(bool exclude);

            Cell &getCell(const size_t &x, const size_t &y);
            const Cell &getCell(const size_t &x, const size_t &y) const;

            const size_t &getWidth() const;
            const size_t &getHeight() const;

            Area getAvailablePaths(const size_t &x, const size_t &y, const size_t &maxStep);

            Path findPath(const size_t &x, const size_t &y, const size_t &target_x, const size_t &target_y);

            Path findShortestPathTo(
                const int64_t &fromX,
                const int64_t &fromY,
                const int64_t &toX,
                const int64_t &toY,
                const int64_t &maxStep
            );
    };

    Area pathToArea(const Path &path);
}

template<>
struct std::hash<std::pair<emblem::Point, emblem::CellType>> {
    size_t operator()(const std::pair<emblem::Point, emblem::CellType> &pair) const {
        return std::hash<size_t>()(pair.first.x) ^ std::hash<size_t>()(pair.first.y);
    }
};

template<>
struct std::hash<emblem::Point> {
    size_t operator()(const emblem::Point &point) const {
        return std::hash<size_t>()(point.x) ^ std::hash<size_t>()(point.y);
    }
};
