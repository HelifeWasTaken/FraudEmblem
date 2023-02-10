struct Point
{
    int x;
    int y;
};

class Map
{
private:
    static const int EMPTY_CELL = -1;
    static const int WALL_CELL = -2;

    unsigned int width;
    unsigned int height;

    int **map;

public:
    Map(int width, int height)
    {
        this->width = width;
        this->height = height;

        map = new int*[height];
        for (int i = 0; i < height; i++)
        {
            map[i] = new int[width];
            for (int j = 0; j < width; j++)
            {
                map[i][j] = EMPTY_CELL;
            }
        }
    }

    ~Map()
    {
        for (int i = 0; i < height; i++)
        {
            delete[] map[i];
        }
        delete[] map;
    }

    void setWall(int x, int y)
    {
        map[y][x] = WALL_CELL;
    }

    void setEmpty(int x, int y)
    {
        map[y][x] = EMPTY_CELL;
    }

    void setCell(int x, int y, int value)
    {
        map[y][x] = value;
    }

    bool isWall(int x, int y)
    {
        return map[y][x] == WALL_CELL;
    }

    bool isEmpty(int x, int y)
    {
        return map[y][x] == EMPTY_CELL;
    }

    int getCell(int x, int y)
    {
        return map[y][x];
    }

    int getWidth()
    {
        return width;
    }

    int getHeight()
    {
        return height;
    }

    // You cannot go through walls in diagonal directions and behind players
    std::vector<Point> getAviablePaths(int x, int y, int maxStep)
    {
        std::vector<Point> result;
        if (maxStep == 0)
        {
            return result;
        }

        if (x > 0 && !isWall(x - 1, y))
        {
            result.push_back({ x - 1, y });
            if (map[y][x - 1] == EMPTY_CELL)
            {
                auto subResult = getAviablePaths(x - 1, y, maxStep - 1);
                result.insert(result.end(), subResult.begin(), subResult.end());
            }
        }
        if (x < width - 1 && !isWall(x + 1, y))
        {
            result.push_back({ x + 1, y });
            if (map[y][x + 1] == EMPTY_CELL)
            {
                auto subResult = getAviablePaths(x + 1, y, maxStep - 1);
                result.insert(result.end(), subResult.begin(), subResult.end());
            }
        }
        if (y > 0 && !isWall(x, y - 1))
        {
            result.push_back({ x, y - 1 });
            if (map[y - 1][x] == EMPTY_CELL)
            {
                auto subResult = getAviablePaths(x, y - 1, maxStep - 1);
                result.insert(result.end(), subResult.begin(), subResult.end());
            }
        }
        if (y < height - 1 && !isWall(x, y + 1))
        {
            result.push_back({ x, y + 1 });
            if (map[y + 1][x] == EMPTY_CELL)
            {
                auto subResult = getAviablePaths(x, y + 1, maxStep - 1);
                result.insert(result.end(), subResult.begin(), subResult.end());
            }
        }
        return result;
    }

    std::vector<Point> findPath(int x, int y, int target_x, int target_y)
    {
        std::vector<Point> result;
        if (x == target_x && y == target_y)
        {
            return result;
        }

        std::vector<Point> aviablePaths = getAviablePaths(x, y, 1);
        for (auto path : aviablePaths)
        {
            if (path.x == target_x && path.y == target_y)
            {
                result.push_back(path);
                return result;
            }
        }

        for (auto path : aviablePaths)
        {
            auto subResult = findPath(path.x, path.y, target_x, target_y);
            if (subResult.size() > 0)
            {
                result.push_back(path);
                result.insert(result.end(), subResult.begin(), subResult.end());
                return result;
            }
        }

        return result;
    }

    std::vector<Point> findShortestPathTo(int fromX, int fromY, int toX, int toY, int maxStep)
    {
        std::vector<Point> result;
        if (fromX == toX && fromY == toY)
        {
            return result;
        }
        if (maxStep == 0)
        {
            return result;
        }

        std::vector<Point> aviablePaths = getAviablePaths(fromX, fromY, 1);
        for (auto path : aviablePaths)
        {
            if (path.x == toX && path.y == toY)
            {
                result.push_back(path);
                return result;
            }
        }

        std::vector<std::vector<Point>> paths;
        for (auto path : aviablePaths)
        {
            auto subResult = findShortestPathTo(path.x, path.y, toX, toY, maxStep - 1);
            if (subResult.size() > 0)
            {
                subResult.push_back(path);
                paths.push_back(subResult);
            }
        }

        if (paths.size() == 0)
        {
            return result;
        }

        int minPathLength = paths[0].size();
        int minPathIndex = 0;
        int minDistance = INT_MAX;
        for (int i = 1; i < paths.size(); i++)
        {
            int distance = abs(paths[i][0].x - toX) + abs(paths[i][0].y - toY);
            if (paths[i].size() < minPathLength ||
                (paths[i].size() == minPathLength && distance < minDistance))
            {
                minPathLength = paths[i].size();
                minPathIndex = i;
                minDistance = distance;
            }
        }

        result = paths[minPathIndex];
        return result;
    }
};