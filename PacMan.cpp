#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "maze_object.h"
#include "pacman_object.h"
#include "dot_object.h"
#include "ghost_object.h"
#include <iostream>

using namespace std;

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

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                isPaused = !isPaused;
            }

			if (!isPaused) {
				pacman.handleInput(event);
			}
        }

        bool allDotsEaten = false;
        /*for (const auto& dot : dots) {
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
            for (auto& dot : dots) {
                dot.draw(window);
            }
			pacman.draw(window);
			pacman.move(maze);

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