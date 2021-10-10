#include "UI.h"
#include <SFML/Graphics.hpp>




void UI::Draw(sf::RenderWindow& window)
{
	sf::Font font;
	if (!font.loadFromFile("font.ttf")) {
		throw "font not found";
	}
	sf::Text buttonText;
	buttonText.setFont(font);
	buttonText.setString("Score: " + std::to_string(board.score));
	buttonText.setCharacterSize(24);
	buttonText.setFillColor(sf::Color::Red);
	buttonText.setPosition(window.getSize().x - 200, 50);

	window.draw(buttonText);
}
