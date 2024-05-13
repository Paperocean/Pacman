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
#include <queue>

using namespace std;

class Pacman {
public:
    sf::Vector2f position;
    sf::Vector2f direction;
    int lives;
    float speed;
    int score;
	int radius;
    list<sf::Vector2f> path; 
    float progress;

    Pacman(const Maze& maze);
    void initializePath(const Maze& maze);
    bool isNextPointInDirection(const sf::Vector2f& newDirection);
    void move(const Maze& maze);
    bool isValidDirection(const sf::Vector2f& newDirection, const Maze& maze);
    void handleInput(sf::Event& event, const Maze& maze);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getCenter() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getDirection() const;
};

#endif // !PACMANOBJECT_H
