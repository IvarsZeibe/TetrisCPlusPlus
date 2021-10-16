#include "Board.h"
#include <vector>
#include <chrono>
#include "TetrominoShape.h"
#include <SFML\Graphics.hpp>
#include "Tile.h"


Board::Board(int width, int height)
{
    board.resize(height, std::vector<Tile>(width, Tile()));
}

void Board::FullFall() {
    if (!isTetrominoFalling) {
        return;
    }
    while (true) {
        if (!Move(0, 1)) {
            StopFalling();
            timeSinceFall = fallCooldown - 100;
            break;
        }
    }
}

void Board::SetNormalFallSpeed()
{
    fallCooldown = 100 + 400 / GetLevel();
}
void Board::SetFastFallSpeed()
{
    fallCooldown = 100;
}

int Board::GetLevel()
{
    int level = (totalLinesCleared / 2) + 1;
    if (level > 10) {
        level = 10;
    }
    return level;
}

void Board::Update(float deltaTime)
{
    if (isGameOver || isPaused) {
        return;
    }
    gameTime += deltaTime;
    timeSinceFall += deltaTime;
    if(timeSinceFall > fallCooldown) {
        if (isTetrominoFalling && !Move(0, 1)) {
            StopFalling();
        }
        RemoveFullLines();
        TryAddTetromino(GetRandomShape());
        timeSinceFall = 0;
    }
}

Tile Board::TileAt(int x, int y)
{
    return board[y][x];
}

void Board::TryAddTetromino(TetrominoShape tetromino)
{
    if (!isTetrominoFalling) {
        tetrominoColor = GetRandomColor();
        int xOffset = (GetWidth() - tetromino.GetWidth()) / 2;
        tetrominoPosition = { xOffset, 0 };
        tetrominoShape = tetromino;

        while (tetrominoShape.GetHeight() > 0) {
            if (CanPlaceTetromino(xOffset, 0, tetrominoShape)) {
                for (int y = 0; y < tetrominoShape.GetHeight(); y++) {
                    for (int x = 0; x < tetrominoShape.GetWidth(); x++) {
                        if (tetrominoShape.tilePositions[y][x] == 1) {
                            board[y][xOffset + x] = Tile(tetrominoColor, true);
                        }
                    }
                }
                break;
            }
            else {
                isGameOver = true;
            }
            tetrominoShape.tilePositions.erase(tetrominoShape.tilePositions.begin());
        }
        if (!isGameOver) {
            isTetrominoFalling = true;
        }
        else {
            tetrominoShape = TetrominoShape::NONE;
        }

    }

}
void Board::Rotate(bool left)
{
    RemoveFallingTetromino();
    tetrominoShape.Rotate(left);
    if (Move(0, 0)) {
        return;
    }
    for (int i = 1; i < tetrominoShape.GetHeight() - 1; i++) {
        if (Move(i, 0) || Move(-i, 0)) {
            return;
        }
    }
    for (int i = 1; i < tetrominoShape.GetHeight() - 1; i++) {
        if (Move(0, i) || Move(0, -i)) {
            return;
        }
    }
    tetrominoShape.Rotate(!left);
    Move(0, 0);
}
void Board::Pause()
{
    isPaused = true;
}
void Board::Unpause()
{
    isPaused = false;
}
bool Board::Move(int xOffset = 0, int yOffset = 0)
{
    if (CanPlaceTetromino(tetrominoPosition.first + xOffset, tetrominoPosition.second + yOffset, tetrominoShape)) {
        RemoveFallingTetromino();
        tetrominoPosition.first += xOffset;
        tetrominoPosition.second += yOffset;
        for (int y = 0; y < tetrominoShape.GetHeight(); y++) {
            for (int x = 0; x < tetrominoShape.GetWidth(); x++) {
                if (tetrominoShape.tilePositions[y][x] == 1) {
                    board[y + tetrominoPosition.second][x + tetrominoPosition.first] = Tile(tetrominoColor, true);
                }
            }
        }
        return true;
    }
    return false;
}
void Board::StopFalling()
{
    isTetrominoFalling = false;
    for (int y = 0; y < tetrominoShape.GetHeight(); y++) {
        if (y + tetrominoPosition.second < 0 || y + tetrominoPosition.second >= GetHeight()) {
            continue;
        }
        for (int x = 0; x < tetrominoShape.GetWidth(); x++) {
            if (x + tetrominoPosition.first < 0 || x + tetrominoPosition.first >= GetWidth()) {
                continue;
            }
            if (tetrominoShape.tilePositions[y][x] == 1) {
                board[y + tetrominoPosition.second][x + tetrominoPosition.first].type = TileType::Frozen;
                score += 2;
            }
        }
    }
}
void Board::RemoveFullLines() {
    int linesRemoved = 0;
    for (int y = GetHeight() - 1 - linesRemoved; y >= 0; y--) {
        bool unfullRowFound = false;
        int rowsRemovedInARow = 0;
        while (!unfullRowFound) {
            int rowFullness = 0;
            for (int x = 0; x < GetWidth(); x++) {
                if (board[y][x].type == TileType::Frozen) {
                    rowFullness++;
                }
                else {
                    unfullRowFound = true;
                    break;
                }
            }
            if (rowFullness == GetWidth()) {
                linesRemoved++;
                totalLinesCleared++;
                rowsRemovedInARow++;
                score += 100 * rowsRemovedInARow;
            }
            if (y - linesRemoved < 0) {
                board[y] = std::vector<Tile>(GetWidth(), Tile::Empty);
            }
            else {
                board[y] = board[y - linesRemoved];
            }
        }
    }
}
sf::Color Board::GetRandomColor()
{
    srand(time(NULL));
    switch (rand() % 5)
    {
    case 0:
        return sf::Color::Blue;
    case 1:
        return sf::Color::Red;
    case 2:
        return sf::Color::Yellow;
    case 3:
        return sf::Color::Green;
    case 4:
        return sf::Color::Cyan;
    }
}
TetrominoShape Board::GetRandomShape() {
    srand(time(NULL));
    switch (rand() % 7)
    {
    case 0:
        return TetrominoShape::I;
    case 1:
        return TetrominoShape::J;
    case 2:
        return TetrominoShape::L;
    case 3:
        return TetrominoShape::O;
    case 4:
        return TetrominoShape::S;
    case 5:
        return TetrominoShape::T;
    case 6:
        return TetrominoShape::Z;
    }
}

bool Board::CanPlaceTetromino(int xPos, int yPos, TetrominoShape tetromino)
{
    for (int y = 0; y < tetromino.GetHeight(); y++) {
        for (int x = 0; x < tetromino.GetWidth(); x++) {
            if (tetromino.tilePositions[y][x] == 1) {
                if (y + yPos < 0 || y + yPos > GetHeight() - 1 ||
                    x + xPos < 0 || x + xPos > GetWidth() - 1 ||
                    board[y + yPos][x + xPos].type == TileType::Frozen) {
                        return false;
                }
            }
        }
    }
    return true;
}
void Board::RemoveFallingTetromino()
{
    for(int y = 0; y < tetrominoShape.GetHeight(); y++) {
        for (int x = 0; x < tetrominoShape.GetWidth(); x++) {
            if (tetrominoShape.tilePositions[y][x] == 1 &&
                y + tetrominoPosition.second >= 0 && y + tetrominoPosition.second < GetHeight() &&
                x + tetrominoPosition.first >= 0 && x + tetrominoPosition.first < GetWidth() &&
                board[y + tetrominoPosition.second][x + tetrominoPosition.first].type == TileType::Falling){
                board[y + tetrominoPosition.second][x + tetrominoPosition.first] = Tile::Empty;
            }
        }
    }
}
