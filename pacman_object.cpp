#include "pacman_object.h"
#include <iostream>

using namespace std;

Pacman::Pacman(float startX, float startY)
{
	position = sf::Vector2f(startX, startY);
	direction = sf::Vector2f(0, 0);
	lives = 3;
	speed = 3.0f;
	score = 0;
	currentFrame = 0;

	/*if (!texture.loadFromFile("pacman.png"))
	{
		std::cerr << "Error loading pacman.png" << std::endl;
		exit(1);
	}

	texture.setSmooth(true);*/
}

void Pacman::move(const std::vector<std::vector<int>>& maze, std::vector<Dot>& dots, int TILE_SIZE)
{
	// SprawdŸ, czy Pacman jest na œcianie
	if (isPathClear(maze, TILE_SIZE, direction)) {
		position += direction * speed;
		for (Dot& dot : dots) {
			if (!dot.isEaten()) {
				sf::Vector2f diff = dot.getPosition() - position;
				if (sqrt(diff.x * diff.x + diff.y * diff.y) < TILE_SIZE / 2.5) {
					dot.eat();
					eatDot();
				}
			}
		}
	}
	else
	{
		moveBack();
		direction = sf::Vector2f(0, 0);
	}
}

void Pacman::eatDot()
{
	score += 10;
}

void Pacman::draw(sf::RenderWindow& window, int TILE_SIZE) {
	sf::CircleShape circle(TILE_SIZE / 3); // Promieñ to po³owa rozmiaru kafelka
	circle.setFillColor(sf::Color::Yellow);
	circle.setPosition(position.x + 1, position.y + 1); // Dodajemy 1, aby utworzyæ margines
	window.draw(circle);
}


void Pacman::handleInput(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			direction = sf::Vector2f(0, -1);
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			direction = sf::Vector2f(0, 1);
		}
		else if (event.key.code == sf::Keyboard::Left)
		{
			direction = sf::Vector2f(-1, 0);
		}
		else if (event.key.code == sf::Keyboard::Right)
		{
			direction = sf::Vector2f(1, 0);
		}
	}
}

void Pacman::setDirection(sf::Vector2f newDirection)
{
	direction = newDirection;
}

void Pacman::collidesWith(std::vector<std::vector<int>>& maze, int TILE_SIZE)
{
	int tileX = static_cast<int>(position.x + 1) / TILE_SIZE; // Dodajemy margines
	int tileY = static_cast<int>(position.y + 1) / TILE_SIZE; // Dodajemy margines

	if (maze[tileY][tileX] == 3)
	{
		maze[tileY][tileX] = 0;
		score += 50;
	}
	else if (maze[tileY][tileX] == 2)
	{
		lives--;
		position = sf::Vector2f(1 * TILE_SIZE, 1 * TILE_SIZE);
	}
	cout << "Lives: " << lives << endl;
	cout << "Score: " << score << endl;
	cout << "Position: " << position.x << ", " << position.y << endl;
}

bool Pacman::isPathClear(const std::vector<std::vector<int>>& maze, int TILE_SIZE, sf::Vector2f newDirection)
{
	sf::Vector2f newPosition = position + newDirection * speed;
	int tileX = static_cast<int>(newPosition.x) / TILE_SIZE;
	int tileY = static_cast<int>(newPosition.y + 1) / TILE_SIZE; // Dodajemy margines tylko do dolnej krawêdzi

	if (maze[tileY][tileX] != 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Pacman::moveBack() {
	position -= direction * speed;
}
