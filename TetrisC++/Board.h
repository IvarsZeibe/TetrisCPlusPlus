#pragma once
#include <vector>
class Board
{
public:
	Board(int width, int height);
	void Update();
	int TileAt(int x, int y);
	void SetTile(int x, int y, int value);
	int GetWidth() {
		return width;
	}
	int GetHeight() {
		return height;
	}
private:
	std::vector<std::vector<int>> board;
	int width;
	int height;
	//int board[20][10];
};

