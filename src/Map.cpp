/*
** EPITECH PROJECT, 2023
** FraudEmblem
** File description:
** Map
*/

#include "Map.hpp"

emblem::Map::Map(const size_t &width, const size_t &height) : __width(width), __height(height) {
    __map.reserve(width);

    for (auto entry : __map)
        entry.reserve(height);
}

void emblem::Map::setWall(const size_t &x, const size_t &y) {
    __map[x][y].setCellType(WALL);
}

void emblem::Map::setEmpty(const size_t &x, const size_t &y) {
    __map[x][y].setCellType(EMPTY);
}

void emblem::Map::setEntity(const size_t &x, const size_t &y, const uint8_t &type) {
    __map[x][y].setCellType(ENTITY);
    __map[x][y].setEntityType(type);
}

void emblem::Map::setCell(const size_t &x, const size_t &y, const emblem::Cell &value) {
    __map[x][y] = value;
}

bool emblem::Map::isWall(const size_t &x, const size_t &y) const {
    return __map[x][y].getCellType() == WALL;
}

bool emblem::Map::isEmpty(const size_t &x, const size_t &y) const {
    return __map[x][y].getCellType() == EMPTY;
}

bool emblem::Map::isEntity(const size_t &x, const size_t &y) const {
    return __map[x][y].getCellType() == ENTITY;
}

bool emblem::Map::isHero(const size_t &x, const size_t &y) const {
    return __map[x][y].getEntityType() == HERO;
}

bool emblem::Map::isVillain(const size_t &x, const size_t &y) const {
    return __map[x][y].getEntityType() == VILLAIN;
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
emblem::Path emblem::Map::getAviablePaths(const size_t &x, const size_t &y, const size_t &maxStep) {
    emblem::Path result;

    if (maxStep == 0) {
        return result;
    }

    if (x > 0 && !isWall(x - 1, y)) {
        result.push_back({ x - 1, y });
        if (isEmpty(x - 1, y)) {
            auto subResult = getAviablePaths(x - 1, y, maxStep - 1);
            result.insert(result.end(), subResult.begin(), subResult.end());
        }
    }

    if (x < __width - 1 && !isWall(x + 1, y)) {
        result.push_back({ x + 1, y });
        if (isEmpty(x + 1, y)) {
            auto subResult = getAviablePaths(x + 1, y, maxStep - 1);
            result.insert(result.end(), subResult.begin(), subResult.end());
        }
    }

    if (y > 0 && !isWall(x, y - 1)) {
        result.push_back({ x, y - 1 });
        if (isEmpty(x, y - 1)) {
            auto subResult = getAviablePaths(x, y - 1, maxStep - 1);
            result.insert(result.end(), subResult.begin(), subResult.end());
        }
    }

    if (y < __height - 1 && !isWall(x, y + 1)) {
        result.push_back({ x, y + 1 });
        if (isEmpty(x, y + 1)) {
            auto subResult = getAviablePaths(x, y + 1, maxStep - 1);
            result.insert(result.end(), subResult.begin(), subResult.end());
        }
    }
    return result;
}

emblem::Path emblem::Map::findPath(const size_t &x, const size_t &y, const size_t &target_x, const size_t &target_y) {
    emblem::Path result;

    if (x == target_x && y == target_y) {
        return result;
    }

    emblem::Path aviablePaths = getAviablePaths(x, y, 1);
    for (auto path : aviablePaths) {
        if (path.x == target_x && path.y == target_y) {
            result.push_back(path);
            return result;
        }
    }

    for (auto path : aviablePaths) {
        auto subResult = findPath(path.x, path.y, target_x, target_y);
        if (subResult.size() > 0) {
            result.push_back(path);
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

    emblem::Path aviablePaths = getAviablePaths(fromX, fromY, 1);
    for (auto path : aviablePaths) {
        if (path.x == toX && path.y == toY) {
            result.push_back(path);
            return result;
        }
    }

    std::vector<emblem::Path> paths;
    for (auto path : aviablePaths) {
        auto subResult = findShortestPathTo(path.x, path.y, toX, toY, maxStep - 1);
        if (subResult.size() > 0) {
            subResult.push_back(path);
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
