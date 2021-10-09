#include "Tile.h"

Tile::Tile(sf::Color color, bool isFalling)
{
	type = isFalling ? TileType::Falling : TileType::Frozen;
	this->color = color;
}

Tile::Tile()
{
	type = TileType::Empty;
	color = sf::Color(200, 200, 200);
}

Tile Tile::Empty = Tile();
