#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "pacman_object.h";
#include "dot_object.h";

using namespace std;

/*
1.	Utwórz okno
•	Ustaw rozmiar okna: Określ szerokość i wysokość okna w pikselach. | [+]
•	Ustaw tytuł okna: Tytuł, który jest wyświetlany na pasku tytułu okna. | [+]
•	Ustaw ikonę okna: Grafika, która jest wyświetlana jako ikona okna. | [+]
•	Ustaw kolor tła okna: Kolor, który jest wyświetlany na tle okna. | [+]
•	Ustaw szybkość klatek okna: Liczba klatek na sekundę, które okno próbuje wyświetlić. | [+]
•	Ustaw styl okna: Określa, czy okno ma pasek tytułu, przyciski zamykania itp. | [+]
•	Ustaw pozycję okna: Określa, gdzie na ekranie pojawi się okno. | [+]
•	Ustaw widoczność okna: Określa, czy okno jest widoczne. | [+]
•	Ustaw focus okna: Określa, czy okno jest aktywne. | [+]
•	Ustaw kursor myszy okna: Określa wygląd kursora myszy, gdy jest nad oknem. | [+]
•	Ustaw powtarzanie klawiszy okna: Określa, czy okno powinno otrzymywać wielokrotne zdarzenia klawiszy, gdy klawisz jest przytrzymywany. | [+]
2.	Utwórz Pacmana: Stwórz obiekt reprezentujący Pacmana. 
Będzie on miał swoją pozycję, kierunek ruchu i być może inne właściwości, takie jak liczba żyć.
	- Utwórz obiekt Pacmana: Stwórz obiekt reprezentujący Pacmana. | [+]
	- Utwórz pozycję Pacmana: Stwórz zmienną przechowującą pozycję Pacmana na ekranie. | [+]
	- Utwórz kierunek ruchu Pacmana: Stwórz zmienną przechowującą kierunek ruchu Pacmana. | [+]
	- Utwórz liczbę żyć Pacmana: Stwórz zmienną przechowującą liczbę żyć Pacmana. | [+]
	- Utwórz prędkość Pacmana: Stwórz zmienną przechowującą prędkość Pacmana. | [+]
	- Utwórz kropki: Stwórz obiekt reprezentujący kropki, które Pacman może zjadać. | [+]
	- Utwórz punkty: Stwórz zmienną przechowującą liczbę punktów zdobytych przez Pacmana. | [+]
	- Utwórz dźwięki: Stwórz dźwięki, które są odtwarzane, gdy Pacman zjada kropki lub jest zjadany przez ducha.
	- Utwórz animacje: Stwórz animacje, które są odtwarzane, gdy Pacman porusza się w różnych kierunkach.
	- Utwórz kolizje: Stwórz mechanizm kolizji, który sprawdza, czy Pacman zderzył się z duchem lub kropką.
	- Utwórz interakcje: Stwórz interakcje, które pozwalają graczowi kontrolować Pacmana za pomocą klawiszy.
	- Utwórz efekty: Stwórz efekty wizualne, takie jak migający Pacman, gdy jest zjadany przez ducha.
	- Utwórz stan gry: Stwórz zmienną przechowującą stan gry, który określa, czy Pacman żyje, czy jest martwy.
	- Utwórz ekran gry: Stwórz ekran, na którym jest wyświetlany Pacman i inne elementy gry.
	- Utwórz ekran menu: Stwórz ekran, na którym gracz może wybrać tryb gry, ustawienia itp.
	- Utwórz ekran pauzy: Stwórz ekran, na którym gra jest wstrzymywana.
3.	Utwórz ducha: Stwórz obiekt reprezentujący ducha. Podobnie jak Pacman, duch będzie miał swoją pozycję, kierunek ruchu i być może inne właściwości.
4.	Utwórz labirynt: Stwórz strukturę danych reprezentującą labirynt, w którym poruszają się Pacman i duchy. Może to być dwuwymiarowa tablica, gdzie każda komórka reprezentuje jedno pole labiryntu.
5.	Utwórz wynik: Stwórz zmienną przechowującą aktualny wynik gracza. Zwiększaj ją, gdy Pacman zjada kropki, i zmniejszaj, gdy jest zjadany przez duchy.
6.	Utwórz timer: Stwórz timer, który będzie kontrolował upływ czasu w grze. Może on na przykład kontrolować, jak szybko poruszają się Pacman i duchy.
7.	Utwórz pętlę gry: Stwórz główną pętlę gry, która będzie kontrolować cały przebieg gry. W każdym obiegu pętli gry, aktualizujesz stan gry i odświeżasz wyświetlanie.
8.	Utwórz ekran końca gry: Stwórz ekran, który jest wyświetlany, gdy gracz przegrywa grę.
9.	Utwórz ekran wygranej gry: Stwórz ekran, który jest wyświetlany, gdy gracz wygrywa grę.
10.	Utwórz ekran pauzy gry: Stwórz ekran, który jest wyświetlany, gdy gracz pauzuje grę.
11.	Utwórz ekran startu gry: Stwórz ekran, który jest wyświetlany na początku gry.
12.	Utwórz ekran ustawień gry: Stwórz ekran, na którym gracz może zmienić ustawienia gry.
13.	Utwórz ekran napisów końcowych gry: Stwórz ekran, na którym są wyświetlane informacje o twórcach gry.
14.	Utwórz ekran pomocy gry: Stwórz ekran, na którym gracz może zobaczyć instrukcje dotyczące gry.
15.	Utwórz ekran informacji o grze: Stwórz ekran, na którym są wyświetlane informacje o grze.
16.	Utwórz ekran wyjścia z gry: Stwórz ekran, który jest wyświetlany, gdy gracz chce opuścić grę.
17.	Utwórz ekran zapisu gry: Stwórz ekran, na którym gracz może zapisać stan gry.
18.	Utwórz ekran wczytywania gry: Stwórz ekran, na którym gracz może wczytać zapisany stan gry.
*/

const int WIDTH = 20;
const int HEIGHT = 10;
const int TILE_SIZE = 100;

vector<vector<int>> maze = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 2, 1, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

};


// make this labirinth bigger much bigger ahahaha!!!
// make it 20x20
// make it 30x30
// make it 40x40

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH * TILE_SIZE, HEIGHT * TILE_SIZE), "Maze", sf::Style::Fullscreen | sf::Style::Close);
    
    auto image = std::vector<sf::Uint8>{ 70, 130, 180, 255, 70, 130, 180, 255, 70, 130, 180, 255,
                                     70, 130, 180, 255, 70, 130, 180, 255, 70, 130, 180, 255,
                                     70, 130, 180, 255, 70, 130, 180, 255, 70, 130, 180, 255 };
    auto size = sf::Vector2u{ 3, 3 };

    window.setIcon(size.x, size.y, image.data());
    window.setFramerateLimit(60);
	window.setVisible(true);
	window.setKeyRepeatEnabled(true);
	window.setMouseCursorVisible(true);
	window.requestFocus();
    window.setKeyRepeatEnabled(false);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width / 2 - WIDTH * TILE_SIZE / 2, desktop.height / 2 - HEIGHT * TILE_SIZE / 2));

    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Hand)) {
        window.setMouseCursor(cursor);
    }

    // PACMAN
    Pacman pacman(WIDTH * TILE_SIZE / 2, (HEIGHT - 1) * TILE_SIZE / 2);
    
    // DOTS
    std::vector<Dot> dots;
    for (int i = 0; i < HEIGHT - 1; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (maze[i][j] == 0) {
                dots.push_back(Dot(j * TILE_SIZE + TILE_SIZE / 2, i * TILE_SIZE + TILE_SIZE / 2));
            }
        }
    }


    std::vector<sf::RectangleShape> obstacles;
    for (int i = 0; i < HEIGHT - 1; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (maze[i][j] == 1)
            {
                sf::RectangleShape wall(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                wall.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                wall.setFillColor(sf::Color::Black);
                obstacles.push_back(wall);
            }
            else if (maze[i][j] == 2)
            {
                sf::RectangleShape wall(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                wall.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                wall.setFillColor(sf::Color::Yellow);
                obstacles.push_back(wall);
            }
            else {
                // settings for color of path
				sf::RectangleShape path(sf::Vector2f(TILE_SIZE, TILE_SIZE));
				path.setPosition(j * TILE_SIZE, i * TILE_SIZE);
				path.setFillColor(sf::Color::Blue);
                obstacles.push_back(path);
            }

        }
    }

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
		std::cerr << "Error loading arial.ttf" << std::endl;
		return 1;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24); // w pikselach
    scoreText.setFillColor(sf::Color::White);

    bool gameOver = false;
	bool gameWon = false;
    bool isPaused = false;

    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Check if the 'Esc' key was pressed
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                isPaused = !isPaused;
            }
        }

        // Check if all dots are eaten
        bool allDotsEaten = true;
        for (const auto& dot : dots) {
            if (!dot.isEaten()) {
                allDotsEaten = false;
                break;
            }
        }

        // If all dots are eaten, set game over
        if (pacman.lives == 0) {
            gameOver = true;
		}
        else if (allDotsEaten) {
            gameWon = true;
        }

        // If game over, display "Game Over!" message
        if (isPaused) {
            sf::Text pauseMenu;
            pauseMenu.setFont(font);
            pauseMenu.setCharacterSize(50);
            pauseMenu.setFillColor(sf::Color::White);
            pauseMenu.setString("Pause Menu\nPress 'Esc' to resume\nPress 'Enter' to quit");

            // Center the text
            pauseMenu.setPosition((WIDTH * TILE_SIZE - pauseMenu.getLocalBounds().width) / 2,
                (HEIGHT * TILE_SIZE - pauseMenu.getLocalBounds().height) / 2);

            window.clear();
            window.draw(pauseMenu);

            // Check if the 'Enter' key was pressed
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                window.close();
            }
        }
        else if (gameOver) {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(50);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setString("Game Over!\n Points: " + std::to_string(pacman.score));

            // Center the text
            gameOverText.setPosition((WIDTH * TILE_SIZE - gameOverText.getLocalBounds().width) / 2,
                (HEIGHT * TILE_SIZE - gameOverText.getLocalBounds().height) / 2);

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
			gameWonText.setString("You won!\n Points: " + std::to_string(pacman.score));

			// Center the text
			gameWonText.setPosition((WIDTH * TILE_SIZE - gameWonText.getLocalBounds().width) / 2,
				(HEIGHT * TILE_SIZE - gameWonText.getLocalBounds().height) / 2);

			window.clear();
			window.draw(gameWonText);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                window.close();
            }
		}
        else {
            // Clear the window
            window.clear();

            // Draw walls
            for (const auto& obstacle : obstacles)
            {
				window.draw(obstacle);
			}

			if (!gameOver) {
				pacman.collidesWith(maze, TILE_SIZE);
            }

            // Draw dots
            for (auto& dot : dots) {
                dot.draw(window, TILE_SIZE);
            }

            // Handle pacman movement
            pacman.handleInput(event);
            pacman.move(maze, dots, TILE_SIZE);
            pacman.draw(window, TILE_SIZE);

            // Display the score text
            scoreText.setString("Score Pacman 1: " + std::to_string(pacman.score));
            scoreText.setPosition(10, 10);
            window.draw(scoreText);

            for (int i = 0; i < pacman.lives; ++i) {
                sf::Text heart;
                heart.setFont(font);
                heart.setString("<3");
                heart.setCharacterSize(24);
                heart.setFillColor(sf::Color::Red);
                heart.setPosition(window.getSize().x - (i + 1) * 30, 0);
                window.draw(heart);
            }
        }

        window.display();
    }

    return 0;
}