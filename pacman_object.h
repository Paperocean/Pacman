#ifndef PACMANOBJECT_H
#define PACMANOBJECT_H

#include <SFML/Graphics.hpp>
#include "dot_object.h"

class Pacman {
public:
    sf::Vector2f position;
    sf::Vector2f direction;
    int lives;
    float speed;
    int score;
    sf::Texture texture;
    int currentFrame;

    Pacman(float startX, float startY);

    void move(const std::vector<std::vector<int>>& maze, std::vector<Dot>& dots, int TILE_SIZE);
    void eatDot();
    void draw(sf::RenderWindow& window, int TILE_SIZE);
	void handleInput(sf::Event& event);
	void setDirection(sf::Vector2f newDirection);
	void collidesWith(std::vector<std::vector<int>>& maze, int TILE_SIZE);
	bool isPathClear(const std::vector<std::vector<int>>& maze, int TILE_SIZE, sf::Vector2f newDirection);
    sf::FloatRect getGlobalBounds(int TILE_SIZE) const;
	void moveBack();
};

#endif // !PACMANOBJECT_H