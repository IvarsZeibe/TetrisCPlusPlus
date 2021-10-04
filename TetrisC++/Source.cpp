#include <SFML/Graphics.hpp>
#include "Board.h"
#include <chrono>

int main() {
	const int WINDOW_WIDTH = 450;
	const int WINDOW_HEIGHT = 800;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris");

	Board board(10, 20);
	board.SetTile(0, 0, 2);
	board.SetTile(5, 4, 2);
	board.SetTile(5, 6, 2);
	board.SetTile(0, 7, 2);
	board.SetTile(1, 7, 2);
	board.SetTile(2, 7, 2);
	board.SetTile(3, 7, 2);
	board.SetTile(4, 7, 2);
	board.SetTile(5, 7, 2);
	board.SetTile(6, 7, 2);
	board.SetTile(7, 7, 2);
	board.SetTile(8, 7, 2);
	board.SetTile(9, 7, 2);
	board.SetTile(5, 7, 2);
	board.SetTile(5, 19, 1);

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	int updateRate = 500;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		int timespan = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
		if (timespan > updateRate) {
			board.Update();
			begin = std::chrono::steady_clock::now();
		}

		window.clear(sf::Color::White);
		for (int y = 0; y < board.GetHeight(); y++) {
			for (int x = 0; x < board.GetWidth(); x++)
			{
				sf::RectangleShape square(sf::Vector2f(20, 20));
				switch (board.TileAt(x, y))
				{
				case 0:
					square.setFillColor(sf::Color(200,200,200));
					break;
				case 1:
					square.setFillColor(sf::Color::Blue);
					break;
				case 2:
					square.setFillColor(sf::Color::Cyan);
					break;
				default:
					break;
				}
				square.setPosition(sf::Vector2f(20 * x, 20 * y));
				window.draw(square);
			}
		}
		window.display();

	}
	return 0;
}