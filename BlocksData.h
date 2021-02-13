#pragma once
#include <vector>

struct BlockData
{
	int id;
	int textureLocationId;
};

struct BlocksData
{
	std::vector<BlockData> blocks;
};

