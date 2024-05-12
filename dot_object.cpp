#include "dot_object.h"

Dot::Dot(sf::Vector2f position, int TILE_SIZE)
{
	this->position = position;
	this->radius = TILE_SIZE / 9;
	this->eaten = false;
}

void Dot::draw(sf::RenderWindow& window) {
    if (!eaten) {
        sf::CircleShape circle(radius);
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(position.x - radius, position.y - radius); 
        window.draw(circle);
    }
}

void Dot::eat()
{
	eaten = true;
}

bool Dot::isEaten() const
{
	return eaten;
}

sf::Vector2f Dot::getPosition() const
{
	return position;
}
