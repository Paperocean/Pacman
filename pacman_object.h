#ifndef PACMANOBJECT_H
#define PACMANOBJECT_H

#include <SFML/Graphics.hpp>
#include "dot_object.h"
#include "maze_object.h"
#include <vector>
#include <set>
#include <iostream>
#include <functional>
#include <algorithm>
#include <list>

using namespace std;

struct Vector2fComparator {
    bool operator() (const sf::Vector2f& lhs, const sf::Vector2f& rhs) const {
        if (lhs.x < rhs.x) return true;
        if (rhs.x < lhs.x) return false;
        if (lhs.y < rhs.y) return true;
        if (rhs.y < lhs.y) return false;
        return false;
    }
};

class Pacman {
public:
    sf::Vector2f position;
    sf::Vector2f direction;
    int lives;
    float speed;
    int score;
	int radius;
    set<sf::Vector2f, Vector2fComparator> allowedPositions;
    list<sf::Vector2f> path;

    Pacman(const Maze& maze);
    void move(const Maze& maze);
    void draw(sf::RenderWindow& window);
    void handleInput(sf::Event& event);
    sf::Vector2f getCenter();
};

#endif // !PACMANOBJECT_H
