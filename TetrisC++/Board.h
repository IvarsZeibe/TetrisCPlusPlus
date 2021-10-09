#pragma once
#include <vector>
#include "TetrominoShape.h"
#include <SFML\Graphics.hpp>
#include "Tile.h"
class Board
{
public:
	Board(int width, int height);
	void Update(float deltaTime);
	Tile TileAt(int x, int y);
	void TryAddTetromino(TetrominoShape tetramino);
	int GetWidth() {
		return board[0].size();
	}
	int GetHeight() {
		return board.size();
	}
	void Rotate(bool left);
	bool Move(int xOffset, int yOffset);
	void StopFalling();
private:
	sf::Color GetRandomColor();
	TetrominoShape GetRandomShape();
	std::vector<std::vector<Tile>> board;
	bool isTetrominoFalling = false;
	void RemoveFullLines();

	std::pair<int, int> tetrominoPosition;
	TetrominoShape tetrominoShape = TetrominoShape::NONE;
	sf::Color tetrominoColor;
	bool CanPlaceTetromino(int xPos, int yPos, TetrominoShape tetromino);
	void RemoveFallingTetromino();
};

