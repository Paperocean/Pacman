#include "pacman_object.h"

Pacman::Pacman(const Maze& maze) {
    this->position = sf::Vector2f(1 * maze.getTile() + maze.getTile() / 2, 1 * maze.getTile() + maze.getTile() / 2);
    direction = sf::Vector2f(0, 0);
    lives = 3;
    speed = 2.5f;
    score = 0;
    radius = maze.getTile() / 4;

    /*for (int h = 0; h < maze.getHeight(); h++) {
        for (int w = 0; w < maze.getWidth(); w++) {
            if (maze.getTileAt(h,w) != 1) {
                if (w + 1 < maze.getWidth() && maze.getTileAt(h, w+1) != 1) {
                    allowedPositions.insert(sf::Vector2f((w + 0.5f) * maze.getTile(), (h + 0.5f) * maze.getTile()));
                    allowedPositions.insert(sf::Vector2f((w + 1.5f) * maze.getTile(), (h + 0.5f) * maze.getTile()));
                }
                if (h + 1 < maze.getHeight() && maze.getTileAt(h+1, w) != 1) {
                    allowedPositions.insert(sf::Vector2f((w + 0.5f) * maze.getTile(), (h + 0.5f) * maze.getTile()));
                    allowedPositions.insert(sf::Vector2f((w + 0.5f) * maze.getTile(), (h + 1.5f) * maze.getTile()));
                }
            }
        }
    }

    for (const sf::Vector2f& pos : allowedPositions) {
        std::cout << "Allowed position: (" << pos.x << ", " << pos.y << ")\n";
    }*/

    path.push_back(sf::Vector2f(150, 150));
    path.push_back(sf::Vector2f(150, 250));
    path.push_back(sf::Vector2f(150, 350));
    path.push_back(sf::Vector2f(150, 450));
    path.push_back(sf::Vector2f(150, 550));
    path.push_back(sf::Vector2f(150, 650));
    path.push_back(sf::Vector2f(150, 750));
    path.push_back(sf::Vector2f(150, 850));
    path.push_back(sf::Vector2f(150, 950));
}

void Pacman::move(const Maze& maze) {
    if (!path.empty()) {
        sf::Vector2f endPosition = path.front();
        if (position == endPosition) {
            path.pop_front();
            if (!path.empty()) {
                endPosition = path.front();
            }
        }
        if (!path.empty()) {
            sf::Vector2f direction = endPosition - position;
            float length = sqrt(direction.x * direction.x + direction.y * direction.y);
            direction.x /= length;
            direction.y /= length;
            sf::Vector2f newPosition = position + direction * speed;

            float tile = maze.getTile();
            newPosition.x = round(newPosition.x / tile) * tile;
            newPosition.y = round(newPosition.y / tile) * tile;

            if (allowedPositions.find(newPosition) != allowedPositions.end()) {
                position = newPosition;
            }
        }
    }
}

//void Pacman::move() {
//    sf::Vector2f newPosition = position + direction * speed;
//    if (allowedPositions.find(newPosition) != allowedPositions.end()) {
//        position = newPosition;
//    }
//}

void Pacman::handleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
            direction = sf::Vector2f(0, -1);
            break;
        case sf::Keyboard::Down:
            direction = sf::Vector2f(0, 1);
            break;
        case sf::Keyboard::Left:
            direction = sf::Vector2f(-1, 0);
            break;
        case sf::Keyboard::Right:
            direction = sf::Vector2f(1, 0);
            break;
        default:
            break;
        }
    }
}

sf::Vector2f Pacman::getCenter() {
    return sf::Vector2f(position.x - radius, position.y - radius);
}

void Pacman::draw(sf::RenderWindow& window) {
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Yellow);
    circle.setPosition(getCenter());
    window.draw(circle);
}

