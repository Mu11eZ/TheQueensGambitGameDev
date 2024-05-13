#include "Map.h"
#include "Game.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "ECS/ECS.h"
#include "ECS/Components.h"
extern Manager manager;

Map::Map(std::string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts)
{
	scaledSize = ms * ts;
}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	std::ifstream mapFile(path);
	std::string line;
	std::vector<std::vector<int>> mapData;


	if (!mapFile.is_open()) {
		std::cout << "ERROR: Unable to open file " << path << std::endl;
		return;
	}
	while (std::getline(mapFile, line)) {
		std::istringstream ss(line);
		std::vector<int> row;
		std::string value;
		std::cout << line << std::endl;//writes out the maplines given from the filepath
		while (std::getline(ss, value, ',')) {
			row.push_back(std::stoi(value));
		}
		mapData.push_back(row);
	}

	for (int y = 0; y < sizeY; ++y) {
		for (int x = 0; x < sizeX; ++x) {
			int tileCode = mapData[y][x];
			int srcX = tileCode % 10;
			int srcY = tileCode / 10;
			AddTile(srcX * tileSize, srcY * tileSize, x * scaledSize, y * scaledSize);
			std::cout << srcX << " + " << srcY << std::endl;
		}
	}
	mapFile.ignore();

	//Koden læser den anden del af filen.
	for (int y = 35; y < sizeY + 35; ++y) {
		for (int x = 0; x < sizeX; ++x) {
			int tileCode = mapData[y][x];
			int xline = mapData[y][x];
			std::cout << xline << std::endl;
			if (xline == 1) {
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, (y - 35) * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
		}
	}
	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
	tile.addGroup(Game::groupMap);
}