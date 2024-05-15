#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "maze_object.h"
#include "pacman_object.h"
#include "dot_object.h"
#include "ghost_object.h"
#include <iostream>

using namespace std;

// Struktura reprezentująca węzeł w grafie
struct Node {
    int x, y;
    float distance;
};

// Operator porównujący dla kolejki priorytetowej
struct CompareDistance {
    bool operator()(Node const& p1, Node const& p2) {
        return p1.distance > p2.distance;
    }
};

// Funkcja do pobierania sąsiadów danego węzła
std::vector<Node> getNeighbors(const Maze& maze, Node node) {
    std::vector<Node> neighbors;
    std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // góra, dół, lewo, prawo

    for (auto& direction : directions) {
        int newX = node.x + direction.first;
        int newY = node.y + direction.second;

        if (newX >= 0 && newX < maze.getWidth() && newY >= 0 && newY < maze.getHeight() && maze.getTileAt(newY, newX) != 1) {
            neighbors.push_back(Node{ newX, newY, std::numeric_limits<float>::max() });
        }
    }

    return neighbors;
}

// Funkcja do obliczania odległości między dwoma węzłami
float getDistance(Node node1, Node node2) {
    int dx = node1.x - node2.x;
    int dy = node1.y - node2.y;
    return std::sqrt(dx * dx + dy * dy);
}

std::vector<Node> generatePath(const Maze& maze, Node start, Node goal) {
    int height = maze.getHeight();
    int width = maze.getWidth();
    std::vector<std::vector<float>> distances(height, std::vector<float>(width, std::numeric_limits<float>::max()));
    std::vector<std::vector<Node>> previous(height, std::vector<Node>(width));
    std::priority_queue<Node, std::vector<Node>, CompareDistance> queue;

    start.distance = 0;
    queue.push(start);

    while (!queue.empty()) {
        Node current = queue.top();
        queue.pop();

        if (current.x == goal.x && current.y == goal.y) {
            break;
        }

        for (Node neighbor : getNeighbors(maze, current)) {
            float alt = current.distance + getDistance(current, neighbor);
            if (alt < distances[neighbor.y][neighbor.x]) {
                distances[neighbor.y][neighbor.x] = alt;
                previous[neighbor.y][neighbor.x] = current;
                neighbor.distance = alt;
                queue.push(neighbor);
            }
        }
    }

    std::vector<Node> path;
    for (Node node = goal; node.distance != std::numeric_limits<float>::max(); node = previous[node.y][node.x]) {
        path.push_back(node);
    }

    std::reverse(path.begin(), path.end());

    std::cout << "Generated path with " << path.size() << " nodes\n";
    for (const Node& node : path) {
        std::cout << "(" << node.x << ", " << node.y << ")\n";
    }
    return path;
}

Node handleInput(const sf::Event& event, const Pacman& pacman, const Maze& maze) {
    sf::Vector2f currentPos = pacman.getPosition();
    Node goal;
    goal.x = currentPos.x;
    goal.y = currentPos.y;
    goal.distance = int(std::numeric_limits<float>::max());

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
            goal.y -= 1;
            break;
        case sf::Keyboard::Down:
            goal.y += 1;
            break;
        case sf::Keyboard::Left:
            goal.x -= 1;
            break;
        case sf::Keyboard::Right:
            goal.x += 1;
            break;
        default:
            break;
        }
    }

    std::cout << "Goal set to (" << goal.x << ", " << goal.y << ")\n";

    return goal;
}

int main() {
    Maze maze;
	const int WIDTH = maze.getWidth();
	const int HEIGHT = maze.getHeight();
	const int TILE_SIZE = maze.getTile();

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Pacman", sf::Style::Fullscreen | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setVisible(true);
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(false);
    window.requestFocus();
    window.setPosition(sf::Vector2i(desktop.width / 2 - WIDTH * TILE_SIZE / 2, desktop.height / 2 - HEIGHT * TILE_SIZE / 2));

    // FONT
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading arial.ttf" << std::endl;
        return 1;
    }

    // SCORE TEXT
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);

    // PACMAN
    Pacman pacman(maze);

    // GHOST

	// DOTS
    vector<Dot> dots;

    bool gameOver = false;
    bool gameWon = false;
    bool isPaused = false;

    Node start, goal;
    start.x = pacman.getPosition().x;
    start.y = pacman.getPosition().y;
    start.distance = 0;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                isPaused = !isPaused;
            }

            goal = handleInput(event, pacman, maze);
        }

        bool allDotsEaten = false;
       /* for (const auto& dot : dots) {
            if (!dot.isEaten()) {
                allDotsEaten = false;
                break;
            }
        }*/

        if (allDotsEaten) {
            gameWon = true;
        }

        if (isPaused) {
            sf::Text pauseMenu;
            pauseMenu.setFont(font);
            pauseMenu.setCharacterSize(50);
            pauseMenu.setFillColor(sf::Color::White);
            pauseMenu.setPosition((WIDTH * TILE_SIZE - pauseMenu.getLocalBounds().width) / 2,
                (HEIGHT * TILE_SIZE - pauseMenu.getLocalBounds().height) / 2);
            pauseMenu.setString("Pause Menu\nPress 'Esc' to resume\nPress 'Enter' to quit");

            window.clear();
            window.draw(pauseMenu);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                window.close();
            }
        }
        else if (gameOver) {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(50);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition((WIDTH * TILE_SIZE - gameOverText.getLocalBounds().width) / 2,
                (HEIGHT * TILE_SIZE - gameOverText.getLocalBounds().height) / 2);
            //gameOverText.setString("Game Over!\n Points: " + std::to_string(pacman.score));


            window.clear();
            window.draw(gameOverText);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                window.close();
            }
		}
		else if (gameWon) {
			sf::Text gameWonText;
			gameWonText.setFont(font);
			gameWonText.setCharacterSize(50);
			gameWonText.setFillColor(sf::Color::Green);
			gameWonText.setPosition((WIDTH * TILE_SIZE - gameWonText.getLocalBounds().width) / 2,
				(HEIGHT * TILE_SIZE - gameWonText.getLocalBounds().height) / 2);
            //gameWonText.setString("You won!\n Points: " + std::to_string(pacman.score));

			window.clear();
			window.draw(gameWonText);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                window.close();
            }
		}
        else {
            window.clear();
            maze.draw(window, dots);
            pacman.draw(window);
            for (auto& dot : dots) {
                dot.draw(window);
            }

            // Generate the path
            std::vector<Node> path = generatePath(maze, start, goal);

            // Move Pacman along the path
            for (const Node& node : path) {
                pacman.moveTo(node.x, node.y);
                // You might want to add a delay here, otherwise Pacman will move along the entire path instantly
            }
            start = goal;

            std::cout << "Pacman position: " << pacman.getPosition().x << ", " << pacman.getPosition().y << std::endl;

            //scoreText.setString("Score Pacman 1: " + std::to_string(pacman.score));
            scoreText.setPosition(10, 10);
            window.draw(scoreText);
            /*for (int i = 0; i < pacman.lives; ++i) {
                sf::Text heart;
                heart.setFont(font);
                heart.setString("<3");
                heart.setCharacterSize(24);
                heart.setFillColor(sf::Color::Red);
                heart.setPosition(window.getSize().x - (i + 1) * 30, 0);
                window.draw(heart);
            }*/
        }
        window.display();
    }

    return 0;
}