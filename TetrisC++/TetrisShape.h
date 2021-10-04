#pragma once
#include <vector>
class TetrisShape
{
public:
	std::vector<std::vector<int>> GetShape();
private:
	std::vector<std::vector<int>> shape;
};

