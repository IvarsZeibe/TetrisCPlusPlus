#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
class Input
{
public:
	static std::vector<std::string> actions;
	void Update();
private:
	sf::Keyboard oldKeyboardState;
	sf::Keyboard newKeyboardState = sf::Keyboard();

};

