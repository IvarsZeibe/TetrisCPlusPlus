#pragma once
#include "Board.h"
#include <SFML\Graphics.hpp>
class UI
{
public:
	UI(Board& board) : board(board) {}
	void Draw(sf::RenderWindow& window);
private:
	Board& board;
};

