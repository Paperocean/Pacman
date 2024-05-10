#ifndef DOTOBJECT_H
#define DOTOBJECT_H

#include <SFML/Graphics.hpp>

class Dot {
public:
    sf::Vector2f position;
    bool eaten;

    Dot(float startX, float startY);
	void draw(sf::RenderWindow& window, int TILE_SIZE);
	void eat();
	bool isEaten() const;
	sf::Vector2f getPosition() const;
};

#endif // !DOTOBJECT_H