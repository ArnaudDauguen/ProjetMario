#pragma once
#include <vector>

struct BlockData
{
	int id;
	int textureLocationId;
	bool ignoreCollisions;
	bool isVictoryBlock;
};

struct BlocksData
{
	std::vector<BlockData> blocks;
};

