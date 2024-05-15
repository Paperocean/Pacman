#include "pacman_object.h"

Pacman::Pacman(const Maze& maze) {
    this->position = sf::Vector2f(static_cast<float>(1 * maze.getTile() + maze.getTile() / 2), static_cast<float>(1 * maze.getTile() + maze.getTile() / 2));
    direction = sf::Vector2f(0, 0);
    lives = 3;
    speed = 2.5f;
    score = 0;
    radius = maze.getTile() / 4;
}

void Pacman::moveTo(int x, int y)
{
    this->position.x = x;
    this->position.y = y;
    std::cout << "Pacman moved to (" << x << ", " << y << ")\n";
}

sf::Vector2f Pacman::getCenter() const{
    return sf::Vector2f(position.x - radius, position.y - radius);
}

sf::Vector2f Pacman::getPosition() const
{
	return position;
}

sf::Vector2f Pacman::getDirection() const
{
	return direction;
}

void Pacman::draw(sf::RenderWindow& window) {
    sf::CircleShape circle(static_cast<float>(radius));
    circle.setFillColor(sf::Color::Yellow);
    circle.setPosition(getCenter());
    window.draw(circle);
}

