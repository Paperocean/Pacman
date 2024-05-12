#ifndef GHOST_OBJECT_H
#define GHOST_OBJECT_H

#include <SFML/Graphics.hpp>
#include <vector>

class Ghost {
private:
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;

public:
    Ghost(float startX, float startY);

    void draw(sf::RenderWindow& window, int TILE_SIZE);
    void move(const std::vector<std::vector<int>>& maze, int TILE_SIZE);
	sf::Vector2f getPosition() const;
};

#endif // GHOST_OBJECT_H