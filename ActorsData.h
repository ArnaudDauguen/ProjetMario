#pragma once
#include <vector>

struct ActorData
{
	int type;
	float spawnX;
	float spawnY;
	int	textureLocationId;
};

struct ActorsData
{
	std::vector<ActorData> actors;
};

