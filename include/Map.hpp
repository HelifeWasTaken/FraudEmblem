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

namespace emblem {
    struct Point {
        size_t x;
        size_t y;
    };

    static const size_t MASK_CELL_TYPE = 0x0f;
    static const size_t EXCLUDE_MASK_CELL_TYPE = ~MASK_CELL_TYPE;

    static const size_t MASK_CELL_ENTITY_TYPE = 0xf0;
    static const size_t EXCLUDE_MASK_CELL_ENTITY_TYPE = ~MASK_CELL_ENTITY_TYPE;

    enum CellType {
        EMPTY,
        WALL,
        ENTITY
    };

    enum EntityType {
        HERO,
        VILLAIN,
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
            __data &= EXCLUDE_MASK_CELL_TYPE;
            __data |= (type & 0xf) << 4;
            return *this;
        }

        uint8_t getCellType() const {
            return __data & MASK_CELL_TYPE;
        }

        uint8_t getEntityType() const {
            return (__data & MASK_CELL_ENTITY_TYPE) >> 4;
        }

        private:
            size_t __data = 0;
    };

    using Path = std::vector<Point>;

    class Map {
        size_t __width;
        size_t __height;

        std::vector<std::vector<Cell>> __map;

        public:
            Map(const size_t &width, const size_t &height);
            ~Map();


        void setWall(const size_t &x, const size_t &y);
        void setEmpty(const size_t &x, const size_t &y);
        void setEntity(const size_t &x, const size_t &y, const uint8_t &type);

        void setCell(const size_t &x, const size_t &y, const Cell &value);

        bool isWall(const size_t &x, const size_t &y) const;
        bool isEmpty(const size_t &x, const size_t &y) const;
        bool isEntity(const size_t &x, const size_t &y) const;

        bool isHero(const size_t &x, const size_t &y) const;
        bool isVillain(const size_t &x, const size_t &y) const;

        const Cell &getCell(const size_t &x, const size_t &y) const;

        const size_t &getWidth() const;
        const size_t &getHeight() const;

        Path getAviablePaths(const size_t &x, const size_t &y, const size_t &maxStep);

        Path findPath(const size_t &x, const size_t &y, const size_t &target_x, const size_t &target_y);

        Path findShortestPathTo(
            const int64_t &fromX,
            const int64_t &fromY,
            const int64_t &toX,
            const int64_t &toY,
            const int64_t &maxStep
        );
    };
}
