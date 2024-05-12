#include "ghost_object.h"

Ghost::Ghost(float startX, float startY)
{
	position = sf::Vector2f(startX, startY);
	direction = sf::Vector2f(0, 0);
	speed = 1;
}

void Ghost::draw(sf::RenderWindow& window, int TILE_SIZE) {
    sf::CircleShape circle(TILE_SIZE / 3); // Promieñ to po³owa rozmiaru kafelka
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(position.x + 1, position.y + 1); // Dodajemy 1, aby utworzyæ margines
    window.draw(circle);
}

void Ghost::move(const std::vector<std::vector<int>>& maze, int tileSize)
{
	// SprawdŸ, czy duch jest na œcianie
	if (maze[position.y / tileSize][position.x / tileSize] == 0)
	{
		position += direction * speed;
	}
	else
	{
		direction = sf::Vector2f(0, 0);
	}

	// Zmiana kierunku
	if (rand() % 100 < 5)
	{
		direction = sf::Vector2f(rand() % 3 - 1, rand() % 3 - 1);
	}
}

sf::Vector2f Ghost::getPosition() const
{
	return position;
}
