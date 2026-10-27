#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <queue>
#include <algorithm>

int main()
{
    std::vector<std::vector<char>> maze = {
        {'#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', '#', '#', ' ', '#'},
        {'#', ' ', '#', 'E', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', ' ', '#'},
        {'#', 'S', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#'}
    };

    // Breadth-first search (BFS) to find the shortest path from 'S' to 'E'
    std::queue<std::tuple<int, int>> q;
    std::vector<std::vector<bool>> visited(maze.size(), std::vector<bool>(maze[0].size(), false));
    std::vector<std::vector<std::pair<int, int>>> parent(maze.size(), std::vector<std::pair<int, int>>(maze[0].size(), {-1, -1}));

    // Find the starting point 'S'
    int mazeHeight = static_cast<int>(maze.size()); 
    int mazeWidth = static_cast<int>(maze[0].size());
    int startX = -1, startY = -1;
    for (int i = 0; i < mazeHeight; ++i)
    {
        for (int j = 0; j < mazeWidth; ++j)
        {
            if (maze[i][j] == 'S')
            {
                startX = i;
                startY = j;
                break;
            }
        }
    }

    q.push({startX, startY});
    visited[startX][startY] = true;
    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        if (maze[x][y] == 'E')
        {
            // Reconstruct the path
            std::vector<std::pair<int, int>> path;
            while (x != -1 && y != -1)
            {
                path.push_back({x, y});
                std::tie(x, y) = parent[x][y];
            }
            std::reverse(path.begin(), path.end());

            // Print the path
            for (const auto& p : path)
            {
                std::cout << "(" << p.first << ", " << p.second << ") ";
            }
            std::cout << std::endl;
            return 0;
        }

        // Explore neighbors
        const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (const auto& dir : directions)
        {
            int newX = x + dir.first;
            int newY = y + dir.second;

            // Check if the new position is valid and not visited
            // Because warnings are errors, we need to cast the dimensions of
            // the maze to std::size_type for comparison.
            if (newX >= 0 && newX < mazeHeight && newY >= 0 && newY < mazeWidth &&
                maze[newX][newY] != '#' && !visited[newX][newY])
            {
                visited[newX][newY] = true;
                parent[newX][newY] = {x, y};
                q.push({newX, newY});
            }
        }
    }
}