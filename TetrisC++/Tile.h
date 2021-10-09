#pragma once
#include <SFML/Graphics.hpp>

enum class TileType{ Empty, Falling, Frozen};
class Tile
{
public:
	Tile(sf::Color color, bool isFalling);
	Tile();
	sf::Color color;
	TileType type;
	static Tile Empty;
};

