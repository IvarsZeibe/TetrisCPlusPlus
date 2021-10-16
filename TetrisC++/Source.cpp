#include <SFML/Graphics.hpp>
#include "Board.h"
#include <chrono>
#include "UI.h"

Board board(10, 20);
double timePerUpdate = 500;
std::chrono::steady_clock::time_point gameStartTime;
std::chrono::steady_clock::time_point lastUpdateTime;
const int WINDOW_WIDTH = 450;
const int WINDOW_HEIGHT = 600;

int main() {
	gameStartTime = std::chrono::steady_clock::now();
	lastUpdateTime = gameStartTime;
	UI ui(board);
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris");
	
	while (window.isOpen())
	{
		// Processes events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Q) {
					board.Rotate(true);
				}
				else if (event.key.code == sf::Keyboard::E) {
					board.Rotate(false);
				}
				else if (event.key.code == sf::Keyboard::A) {
					board.Move(-1, 0);
				}
				else if (event.key.code == sf::Keyboard::D) {
					board.Move(1, 0);
				}
				else if (event.key.code == sf::Keyboard::S) {
					board.SetFastFallSpeed();
				}
				else if (event.key.code == sf::Keyboard::Space) {
					board.FullFall();
				}
				else if (event.key.code == sf::Keyboard::P) {
					if (board.isPaused) {
						board.Unpause();
					}
					else {
						board.Pause();
					}
				}
			}
			else if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::S) {
					board.SetNormalFallSpeed();
				}
			}
		}

		// Update
		double deltaTime = (std::chrono::steady_clock::now() - lastUpdateTime) / std::chrono::milliseconds(1);
		board.Update(deltaTime);
		lastUpdateTime = std::chrono::steady_clock::now();

		// Draw
		window.clear(sf::Color::White);
		for (int y = 0; y < board.GetHeight(); y++) {
			for (int x = 0; x < board.GetWidth(); x++)
			{
				sf::RectangleShape square(sf::Vector2f(30, 30));
				square.setFillColor(board.TileAt(x, y).color);
				square.setPosition(sf::Vector2f(30 * x, 30 * y));
				window.draw(square);
			}
		}
		ui.Draw(window);
		window.display();
	}
	return 0;
}
