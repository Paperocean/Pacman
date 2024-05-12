#ifndef DOTOBJECT_H
#define DOTOBJECT_H

#include <SFML/Graphics.hpp>

class Dot {
public:
    sf::Vector2f position;
    bool eaten;
	float radius;

	Dot(sf::Vector2f position, int TILE_SIZE);
	void draw(sf::RenderWindow& window);
	void eat();
	bool isEaten() const;
	sf::Vector2f getPosition() const;
};

#endif // !DOTOBJECT_H