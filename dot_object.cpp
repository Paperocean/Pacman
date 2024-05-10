#include "dot_object.h"

Dot::Dot(float startX, float startY)
{
    position = sf::Vector2f(startX, startY);
    eaten = false;
}

void Dot::draw(sf::RenderWindow& window, int TILE_SIZE)
{
	if (!eaten)
	{
		sf::CircleShape dot(TILE_SIZE / 10);
		dot.setPosition(position);
		dot.setFillColor(sf::Color::Red);
		window.draw(dot);
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
