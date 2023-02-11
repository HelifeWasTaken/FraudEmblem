/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Map
*/

#include "Map.hpp"

emblem::Map::Map(const size_t &width, const size_t &height) : __width(width), __height(height) {
    __map.reserve(width);

    for (size_t i = 0; i < width; i++) {
        __map.emplace_back(std::vector<emblem::Cell>(height));
        for (size_t j = 0; j < height; j++) {
            __map.at(i).push_back(emblem::Cell());
        }
    }
}

void emblem::Map::setWall(const size_t &x, const size_t &y) {
    __map.at(x).at(y).setCellType(WALL);
}

void emblem::Map::setEmpty(const size_t &x, const size_t &y) {
    __map.at(x).at(y).setCellType(EMPTY);
}

void emblem::Map::setEntity(const size_t &x, const size_t &y, const uint8_t &type) {
    __map.at(x).at(y).setCellType(ENTITY);
    __map.at(x).at(y).setEntityType(type);
}

void emblem::Map::setCell(const size_t &x, const size_t &y, const emblem::Cell &value) {
    __map.at(x).at(y) = value;
}

bool emblem::Map::isWall(const size_t &x, const size_t &y) const {
    return __map.at(x).at(y).getCellType() == WALL;
}

bool emblem::Map::isEmpty(const size_t &x, const size_t &y) const {
    return __map.at(x).at(y).getCellType() == EMPTY;
}

bool emblem::Map::isEntity(const size_t &x, const size_t &y) const {
    return __map.at(x).at(y).getCellType() == ENTITY;
}

bool emblem::Map::isHero(const size_t &x, const size_t &y) const {
    return __map.at(x).at(y).getEntityType() == HERO;
}

bool emblem::Map::isVillain(const size_t &x, const size_t &y) const {
    return __map.at(x).at(y).getEntityType() == VILLAIN;
}

emblem::Cell &emblem::Map::getCell(const size_t &x, const size_t &y) {
    return __map.at(x).at(y);
}

const emblem::Cell &emblem::Map::getCell(const size_t &x, const size_t &y) const {
    return __map[x][y];
}

const size_t &emblem::Map::getWidth() const {
    return __width;
}

const size_t &emblem::Map::getHeight() const {
    return __height;
}

// You cannot go through walls in diagonal directions and behind players
emblem::Area emblem::Map::getAviablePaths(const size_t &x, const size_t &y, const size_t &maxStep) {
    emblem::Area result;

    if (maxStep == 0) {
        return result;
    }

    if (x > 0) {
        if (isWall(x - 1, y) || isEntity(x - 1, y)) {
            result.insert(std::make_pair<emblem::Point, emblem::CellType>({ x - 1, y }, WALL));
        } else {
            result.insert(std::make_pair<emblem::Point, emblem::CellType>({ x - 1, y }, EMPTY));
            if (isEmpty(x - 1, y)) {
                auto subResult = getAviablePaths(x - 1, y, maxStep - 1);
                result.merge(subResult);
            }
        }
    }

    if (x < __width - 1) {
        if (isWall(x + 1, y) || isEntity(x + 1, y)) {
            result.insert(std::make_pair<emblem::Point, emblem::CellType>({ x + 1, y }, WALL));
        } else {
            result.insert(std::make_pair<emblem::Point, emblem::CellType>({ x + 1, y }, EMPTY));
            if (isEmpty(x + 1, y)) {
                auto subResult = getAviablePaths(x + 1, y, maxStep - 1);
                result.merge(subResult);
            }
        }
    }

    if (y > 0) {
        if (isWall(x, y - 1) || isEntity(x, y - 1)) {
            result.insert(std::make_pair<emblem::Point, emblem::CellType>({ x, y - 1 }, WALL));
        } else {
            result.insert(std::make_pair<emblem::Point, emblem::CellType>({ x, y - 1 }, EMPTY));
            if (isEmpty(x, y - 1)) {
                auto subResult = getAviablePaths(x, y - 1, maxStep - 1);
                result.merge(subResult);
            }
        }
    }

    if (y < __height - 1) {
        if (isWall(x, y + 1) || isEntity(x, y + 1)) {
            result.insert({{ x, y + 1 }, WALL});
        } else {
            result.insert({{ x, y + 1 }, EMPTY});
            if (isEmpty(x, y + 1)) {
                auto subResult = getAviablePaths(x, y + 1, maxStep - 1);
                result.merge(subResult);
            }
        }
    }
    return result;
}

emblem::Path emblem::Map::findPath(const size_t &x, const size_t &y, const size_t &target_x, const size_t &target_y) {
    emblem::Path result;

    if (x == target_x && y == target_y) {
        return result;
    }

    emblem::Area aviablePaths = getAviablePaths(x, y, 1);
    for (auto &[pos, type] : aviablePaths) {
        if (pos.x == target_x && pos.y == target_y) {
            result.push_back(pos);
            return result;
        }
    }

    for (auto &[pos, type] : aviablePaths) {
        auto subResult = findPath(pos.x, pos.y, target_x, target_y);
        if (subResult.size() > 0) {
            result.push_back(pos);
            result.insert(result.end(), subResult.begin(), subResult.end());
            return result;
        }
    }

    return result;
}

emblem::Path emblem::Map::findShortestPathTo(
    const int64_t &fromX,
    const int64_t &fromY,
    const int64_t &toX,
    const int64_t &toY,
    const int64_t &maxStep)
{
    emblem::Path result;
    if (fromX == toX && fromY == toY) {
        return result;
    }
    if (maxStep == 0) {
        return result;
    }

    emblem::Area aviablePaths = getAviablePaths(fromX, fromY, 1);
    for (auto &[pos, type] : aviablePaths) {
        if (pos.x == toX && pos.y == toY) {
            result.push_back(pos);
            return result;
        }
    }

    std::vector<emblem::Path> paths;
    for (auto &[pos, type] : aviablePaths) {
        auto subResult = findShortestPathTo(pos.x, pos.y, toX, toY, maxStep - 1);
        if (subResult.size() > 0) {
            subResult.push_back(pos);
            paths.push_back(subResult);
        }
    }

    if (paths.size() == 0) {
        return result;
    }

    int minPathLength = paths[0].size();
    int minPathIndex = 0;
    int minDistance = INT_MAX;
    for (int i = 1; i < paths.size(); i++) {
        int distance = std::abs((int64_t)paths[i][0].x - toX) + std::abs((int64_t)paths[i][0].y - toY);
        if (paths[i].size() < minPathLength ||
            (paths[i].size() == minPathLength && distance < minDistance)) {
            minPathLength = paths[i].size();
            minPathIndex = i;
            minDistance = distance;
        }
    }

    result = paths[minPathIndex];
    return result;
}
