#include "pacman_object.h"

Pacman::Pacman(const Maze& maze) {
    this->position = sf::Vector2f(static_cast<float>(1 * maze.getTile() + maze.getTile() / 2), static_cast<float>(1 * maze.getTile() + maze.getTile() / 2));
    direction = sf::Vector2f(0, 0);
    lives = 3;
    speed = 2.5f;
    score = 0;
    radius = maze.getTile() / 4;

    initializePath(maze);
}

void Pacman::initializePath(const Maze& maze) {
    int height = maze.getHeight();
    int width = maze.getWidth();
    float tile = static_cast<float>(maze.getTile());
    float step = tile / 100; // Adjust as needed
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            if (maze.getTileAt(h, w) != 1) {
                if (w + 1 < width && maze.getTileAt(h, w + 1) != 1) {
                    for (float x = w + 0.5f; x <= w + 1.5f; x += step / tile) {
                        sf::Vector2f point(x * tile, (h + 0.5f) * tile);
                        path.push_back(point);
                    }
                }
                if (h + 1 < height && maze.getTileAt(h + 1, w) != 1) {
                    for (float y = h + 0.5f; y <= h + 1.5f; y += step / tile) {
                        sf::Vector2f point((w + 0.5f) * tile, y * tile);
                        path.push_back(point);
                    }
                }
            }
        }
    }
}

bool Pacman::isNextPointInDirection(const sf::Vector2f& newDirection) {
    if (!path.empty()) {
        sf::Vector2f nextPoint = path.front();
        sf::Vector2f directionToNextPoint = nextPoint - position;
        float length = sqrt(directionToNextPoint.x * directionToNextPoint.x + directionToNextPoint.y * directionToNextPoint.y);
        if (length > 0) {
            directionToNextPoint.x /= length;
            directionToNextPoint.y /= length;
        }
        return directionToNextPoint == newDirection;
    }
    return false;
}

void Pacman::move(const Maze& maze) {
    // Check if there are points in the path
    if (!path.empty()) {
        // Get the next point in the path
        sf::Vector2f targetPosition = path.front();

        // Calculate direction towards the target position
        sf::Vector2f nextDirection = targetPosition - position;
        float length = sqrt(nextDirection.x * nextDirection.x + nextDirection.y * nextDirection.y);
        if (length > 0) {
            nextDirection.x /= length;
            nextDirection.y /= length;
        }

        // If the next point is not in the chosen direction, continue moving in the chosen direction
        if (nextDirection != direction) {
            sf::Vector2f newPosition = position + direction * speed;
            int x = static_cast<int>(newPosition.x / maze.getTile());
            int y = static_cast<int>(newPosition.y / maze.getTile());
            if (x >= 0 && x < maze.getWidth() && y >= 0 && y < maze.getHeight() && !maze.isWall(x, y)) {
                position = newPosition;
                return;
            }
        }

        // Move Pacman towards the target position
        sf::Vector2f newPosition = position + nextDirection * speed;
        int x = static_cast<int>(newPosition.x / maze.getTile());
        int y = static_cast<int>(newPosition.y / maze.getTile());
        if (x >= 0 && x < maze.getWidth() && y >= 0 && y < maze.getHeight()) {
            if (!maze.isWall(x, y)) {
                position = newPosition;

                // Check if Pacman has reached the target position
                float epsilon = 0.1f * speed; // Adjust as needed
                if (abs(position.x - targetPosition.x) < epsilon && abs(position.y - targetPosition.y) < epsilon) {
                    // Remove the reached point from the path
                    path.pop_front();
                }
            }
        }
    }
}


bool Pacman::isValidDirection(const sf::Vector2f& newDirection, const Maze& maze) {
    sf::Vector2f newPosition = position + newDirection * speed;
    int x = static_cast<int>(newPosition.x / maze.getTile());
    int y = static_cast<int>(newPosition.y / maze.getTile());
    return x >= 0 && x < maze.getWidth() && y >= 0 && y < maze.getHeight() && !maze.isWall(x, y);
}

void Pacman::handleInput(sf::Event& event, const Maze& maze) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Vector2f newDirection;
        switch (event.key.code) {
        case sf::Keyboard::Up:
            newDirection = sf::Vector2f(0, -1);
            break;
        case sf::Keyboard::Down:
            newDirection = sf::Vector2f(0, 1);
            break;
        case sf::Keyboard::Left:
            newDirection = sf::Vector2f(-1, 0);
            break;
        case sf::Keyboard::Right:
            newDirection = sf::Vector2f(1, 0);
            break;
        default:
            return;
        }
        if (isValidDirection(newDirection, maze) && isNextPointInDirection(newDirection)) {
            direction = newDirection;
        }
    }
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

