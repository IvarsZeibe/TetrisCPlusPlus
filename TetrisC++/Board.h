#pragma once
#include <vector>
#include "TetrominoShape.h"
#include <SFML\Graphics.hpp>
#include "Tile.h"
class Board
{
public:
	Board() {};
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
	void Pause();
	void Unpause();
	bool Move(int xOffset, int yOffset);
	void StopFalling();
	void FullFall();
	int score = 0;
	void SetFastFallSpeed();
	void SetNormalFallSpeed();
	int GetLevel();
	bool isGameOver = false;
	bool isPaused = false;
	int gameTime = 0;
private:
	int totalLinesCleared = 0;
	int fallCooldown = 500;
	int timeSinceFall = 0;
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

