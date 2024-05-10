#ifndef MAZE_OBJECT_H
#define MAZE_OBJECT_H

#include <SFML/Graphics.hpp>

class Maze {
private:
    const int WIDTH = 10;
    const int HEIGHT = 10;
    const int TILE_SIZE = 50;
    int** maze;

public:
    Maze() {
        maze = new int*[HEIGHT];
        for (int i = 0; i < HEIGHT; ++i) {
            maze[i] = new int[WIDTH];
        }

        int initialMaze[HEIGHT][WIDTH] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        };

        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                maze[i][j] = initialMaze[i][j];
            }
        }
    }

    int getTile(int x, int y) const {
        return maze[y][x];
    }

    ~Maze() {
        for (int i = 0; i < HEIGHT; ++i) {
            delete[] maze[i];
        }
        delete[] maze;
    }
};

#endif // !MAZE_OBJECT_H