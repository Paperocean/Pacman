#ifndef MAZE_OBJECT_H
#define MAZE_OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "dot_object.h"
using namespace std;

class Maze {
private:
    const int WIDTH = 20;
    const int HEIGHT = 11;
    const int TILE_SIZE = 100;
    vector<vector<int>> maze;

public:
    Maze() {
        maze = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 3, 3, 3, 0, 3, 0, 1},
            {1, 3, 1, 0, 1, 1, 1, 1, 0, 3, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1},
            {1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 1},
            {1, 3, 1, 0, 1, 1, 0, 1, 0, 0, 3, 0, 2, 1, 0, 1, 1, 0, 3, 1},
            {1, 3, 1, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 3, 1},
            {1, 0, 1, 1, 0, 1, 0, 1, 0, 3, 3, 0, 1, 1, 0, 1, 1, 0, 3, 1},
            {1, 3, 0, 0, 0, 1, 0, 0, 1, 3, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1},
            {1, 3, 3, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 3, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 3, 3, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        };
    }

    int getTile() const {
        return TILE_SIZE;
    }

	int getWidth() const {
		return WIDTH;
	}

    int getHeight() const {
		return HEIGHT;
    }

    int getTileAt(int h, int w) const {
        int tile = maze[h][w];
        std::cout << "getTileAt(" << h << ", " << w << ") = " << tile << std::endl;
        return tile;
    }


    void draw(sf::RenderWindow& window, vector<Dot>& dots) {
		//sf::VertexArray lines(sf::Lines);
        for (int h = 0; h < HEIGHT; h++) {
            for (int w = 0; w < WIDTH; w++) {
                /*if (maze[h][w] != 1) {
                    if (w + 1 < WIDTH && maze[h][w + 1] != 1) {
                        lines.append(sf::Vertex(sf::Vector2f((w + 0.5f) * TILE_SIZE, (h + 0.5f) * TILE_SIZE), sf::Color::Cyan));
                        lines.append(sf::Vertex(sf::Vector2f((w + 1.5f) * TILE_SIZE, (h + 0.5f) * TILE_SIZE), sf::Color::Cyan));
                    }
                    if (h + 1 < HEIGHT && maze[h + 1][w] != 1) {
                        lines.append(sf::Vertex(sf::Vector2f((w + 0.5f) * TILE_SIZE, (h + 0.5f) * TILE_SIZE), sf::Color::Cyan));
                        lines.append(sf::Vertex(sf::Vector2f((w + 0.5f) * TILE_SIZE, (h + 1.5f) * TILE_SIZE), sf::Color::Cyan));
                    }
                }
                window.draw(lines);*/

                sf::RectangleShape rectangle(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                rectangle.setPosition(w * TILE_SIZE, h * TILE_SIZE);
                if (maze[h][w] == 1) {
                    rectangle.setFillColor(sf::Color::Blue);
                    window.draw(rectangle);
                }
                else if (maze[h][w] == 2) {
                    rectangle.setFillColor(sf::Color::Green);
                    window.draw(rectangle);
				}
				else if (maze[h][w] == 3) {
                    dots.push_back(Dot(sf::Vector2f(w * TILE_SIZE + TILE_SIZE / 2, h * TILE_SIZE + TILE_SIZE / 2), TILE_SIZE));
				}
                else {
                    rectangle.setFillColor(sf::Color::Black);
                    window.draw(rectangle);
                }
            }
        }
    }

	bool isWall(int x, int y) const {
		return maze[y][x] == 1;
	}

	void initializeDots(vector<Dot>& dots) {
		for (int h = 0; h < HEIGHT; h++) {
			for (int w = 0; w < WIDTH; w++) {
				if (maze[h][w] == 0) {
					dots.push_back(Dot(sf::Vector2f(w * TILE_SIZE + TILE_SIZE / 2, h * TILE_SIZE + TILE_SIZE / 2), TILE_SIZE));
				}
			}
		}
	}

    std::vector<sf::Vector2f> getNeighbors(sf::Vector2f point) {
        std::vector<sf::Vector2f> neighbors;
        int x = point.x / TILE_SIZE;
        int y = point.y / TILE_SIZE;

        // Sprawd� punkt na g�rze
        if (y - 1 >= 0 && y - 1 < HEIGHT && getTileAt(y - 1, x) != 1) {
            neighbors.push_back(sf::Vector2f(x * TILE_SIZE, (y - 1) * TILE_SIZE));
        }

        // Sprawd� punkt na dole
        if (y + 1 >= 0 && y + 1 < HEIGHT && getTileAt(y + 1, x) != 1) {
            neighbors.push_back(sf::Vector2f(x * TILE_SIZE, (y + 1) * TILE_SIZE));
        }

        // Sprawd� punkt po lewej stronie
        if (x - 1 >= 0 && x - 1 < WIDTH && getTileAt(y, x - 1) != 1) {
            neighbors.push_back(sf::Vector2f((x - 1) * TILE_SIZE, y * TILE_SIZE));
        }

        // Sprawd� punkt po prawej stronie
        if (x + 1 >= 0 && x + 1 < WIDTH && getTileAt(y, x + 1) != 1) {
            neighbors.push_back(sf::Vector2f((x + 1) * TILE_SIZE, y * TILE_SIZE));
        }

        return neighbors;
    }

};

#endif // !MAZE_OBJECT_H