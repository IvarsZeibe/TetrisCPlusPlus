#include "UI.h"
#include <SFML/Graphics.hpp>




void UI::Draw(sf::RenderWindow& window)
{
	sf::Font font;
	if (!font.loadFromFile("font.ttf")) {
		throw "font not found";
	}
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score: " + std::to_string(board.score) +
	"\nTime: " + std::to_string(board.gameTime / 1000) +
	"\nLevel: " + std::to_string(board.GetLevel()) +
	"\n\n\n\n\nControls" + 
	"\nMove: A, D" +
	"\nRotete: Q, E" +
	"\nFaster fall: S" +
	"\nFall: SPACE" +
	"\nPause: P");
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::Red);
	scoreText.setPosition(window.getSize().x - 140, 50);

	window.draw(scoreText);

	if (board.isGameOver) {
		sf::Text gameOver;
		gameOver.setFont(font);
		gameOver.setString("GAME OVER");
		gameOver.setCharacterSize(48);
		gameOver.setFillColor(sf::Color(200, 50, 50));
		gameOver.setPosition(50, 200);
		window.draw(gameOver);
	}
	else if (board.isPaused) {
		sf::Text gameOver;
		gameOver.setFont(font);
		gameOver.setString("PAUSED");
		gameOver.setCharacterSize(48);
		gameOver.setFillColor(sf::Color(200, 50, 50));
		gameOver.setPosition(50, 200);
		window.draw(gameOver);
	}
}
