#pragma once
#include <nlohmann/json.hpp>
#include <fstream>



#include "BlocksData.h"
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

inline void from_json(const json& j, BlocksData& blocks_data)
{
	const json& blocks = j.at("blocks");
	blocks_data.blocks.resize(blocks.size());
	std::copy(blocks.begin(), blocks.end(), blocks_data.blocks.begin());
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


