#include "TetrominoShape.h"
#include <vector>
#include "Tile.h"

TetrominoShape::TetrominoShape(std::vector<std::vector<int>> tilePositions)
{
	this->tilePositions = tilePositions;
}

int TetrominoShape::GetWidth()
{
	return tilePositions[0].size();
}

int TetrominoShape::GetHeight()
{
	return tilePositions.size();
}

void TetrominoShape::Rotate(bool left)
{
	std::vector<std::vector<int>> rotatedTilePositions;
	for (int colon = 0; colon < tilePositions[0].size(); colon++) {
		std::vector<int> rotatedRow;
		for (int row = 0; row < tilePositions.size(); row++) {
			if (left) {
				rotatedRow.push_back(tilePositions[row][tilePositions[0].size() - 1 - colon]);
			}
			else {
				rotatedRow.push_back(tilePositions[tilePositions.size() - 1 - row][colon]);
			}
		}
		rotatedTilePositions.push_back(rotatedRow);
	}
	tilePositions = rotatedTilePositions;
}

TetrominoShape TetrominoShape::NONE = TetrominoShape(
	{
		{0}
	}
);
TetrominoShape TetrominoShape::I = TetrominoShape(
	{
		{0, 0, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 1, 0}
	}
);
TetrominoShape TetrominoShape::O = TetrominoShape(
	{
		{1, 1},
		{1, 1}
	}
);
TetrominoShape TetrominoShape::T = TetrominoShape(
	{
		{0, 1, 0},
		{1, 1, 1},
		{0, 0, 0}
	}
);
TetrominoShape TetrominoShape::S = TetrominoShape(
	{
		{0, 1, 1},
		{1, 1, 0},
		{0, 0, 0}
	}
);
TetrominoShape TetrominoShape::Z = TetrominoShape(
	{
		{1, 1, 0},
		{0, 1, 1},
		{0, 0, 0}
	}
);
TetrominoShape TetrominoShape::J = TetrominoShape(
	{
		{1, 0, 0},
		{1, 1, 1},
		{0, 0, 0}
	}
);
TetrominoShape TetrominoShape::L = TetrominoShape(
	{
		{0, 0, 1},
		{1, 1, 1},
		{0, 0, 0}
	}
);

