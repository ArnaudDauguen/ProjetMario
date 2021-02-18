#pragma once
#include <nlohmann/json.hpp>
#include <fstream>



#include "BlocksData.h"
#include "ActorsData.h"
#include "LevelData.h"
#include "Messager.h"

using json = nlohmann::json;

inline void from_json(const json& j, LevelData& level_data)
{
	j.at("width").get_to(level_data.width);
	j.at("height").get_to(level_data.height);
	j.at("data").get_to(level_data.data);
}

inline void from_json(const json& j, BlockData& block_data)
{
	j.at("id").get_to(block_data.id);
	j.at("textureLocationId").get_to(block_data.textureLocationId);
	j.at("ignoreCollisions").get_to(block_data.ignoreCollisions);
	j.at("isVictoryBlock").get_to(block_data.isVictoryBlock);
}

inline void from_json(const json& j, ActorData& actor_data)
{
	j.at("type").get_to(actor_data.type);
	j.at("spawnX").get_to(actor_data.spawnX);
	j.at("spawnY").get_to(actor_data.spawnY);
	j.at("textureLocationId").get_to(actor_data.textureLocationId);
}

inline void from_json(const json& j, BlocksData& blocks_data)
{
	const json& blocks = j.at("blocks");
	blocks_data.blocks.resize(blocks.size());
	std::copy(blocks.begin(), blocks.end(), blocks_data.blocks.begin());
}

inline void from_json(const json& j, ActorsData& actors_data)
{
	const json& actors = j.at("actors");
	actors_data.actors.resize(actors.size());
	std::copy(actors.begin(), actors.end(), actors_data.actors.begin());
}

class SaveReader
{
public:
	SaveReader() = delete;
	
	static LevelData GetLevelData()
	{
		return LevelData(internalGetData(".\\save\\level.json"));
	}

	static BlocksData GetBlocksData()
	{
		return BlocksData(internalGetData(".\\save\\blocks.json"));
	}


	static ActorsData GetActorsData()
	{
		return ActorsData(internalGetData(".\\save\\actors.json"));
	}

private:
	static json internalGetData(const std::string& path)
	{
		std::ifstream ifs(path);
		
		if (!ifs.good())
		{
			const std::string message = "Could not load file " + path;
			
			Messager::ShowMessageAndExit(message.c_str());
		}

		return json::parse(ifs);
	}
};


