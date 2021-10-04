#include "Board.h"


Board::Board(int width, int height)
{
    this->width = width;
    this->height = height;
    board.resize(height, std::vector<int>(width, 0));
}

void Board::Update()
{
    int rowsRemoved = 0;
    for (int y = height - 1; y >= 0; y--) {
        int rowFullness = 0;
        for (int x = 0; x < width; x++)
        {
            switch (board[y][x])
            {
            case 1:
                rowFullness++;
                board[y][x] = 0;
                board[y + rowsRemoved][x] = 1;
                break;
            case 2:
                if (y == height - 1) {
                    board[y][x] = 1;
                }
                else if (board[y + 1][x] == 0) {
                    board[y + 1][x] = 2;
                    board[y][x] = 0;
                }
                else
                {
                    board[y][x] = 1;
                }
                break;
            default:
                break;
            }
        }
        if (rowFullness == width) {
            rowsRemoved++;
            board[y] = std::vector<int>(width, 0);
        }
    }
}
int Board::TileAt(int x, int y)
{
    return board[y][x];
}

void Board::SetTile(int x, int y, int value)
{
    board[y][x] = value;
}
