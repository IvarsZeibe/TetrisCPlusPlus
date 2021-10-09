#pragma once
#include <vector>
#include "Tile.h"
class TetrominoShape
{
public:
	TetrominoShape(std::vector<std::vector<int>> tilePositions);
	std::vector<std::vector<int>> tilePositions;
	int GetWidth();
	int GetHeight();
	void Rotate(bool left);
	static TetrominoShape NONE;
	static TetrominoShape I;
	static TetrominoShape O;
	static TetrominoShape T;
	static TetrominoShape S;
	static TetrominoShape Z;
	static TetrominoShape J;
	static TetrominoShape L;
};

