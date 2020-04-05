#pragma once
#include "glm/glm.hpp"

struct GameData {
	unsigned int m_Flags = 0;
	bool m_IsOnGame = 0;
	glm::vec2 m_TilemapSize = { 10,10 };
	float m_tileWidth = 5.0f;
	unsigned int m_Mines = 15;
};

class Memory
{
public:

	static Memory& Get() { return m_Instance; }
	~Memory() {}

	static void SetData(const GameData& gamedata) { m_Data = gamedata; }
	static GameData GetData() { return m_Data; }


	static void AddFlag() { m_Data.m_Flags++; }
	static void RemoveFlag() { m_Data.m_Flags--; }

	static void SetFlag(int flag) { m_Data.m_Flags = flag; }
	static int GetFlag() { return m_Data.m_Flags; }

	static void SetGame(bool game) { m_Data.m_IsOnGame = game; }
	static bool GetGame() { return m_Data.m_IsOnGame; }

	static void SetTileWidth(float width) { m_Data.m_tileWidth = width; }
	static float GetTileWidth() { return m_Data.m_tileWidth; }

	static void SetTilemapSize(const glm::vec2& tilemapSize) { m_Data.m_TilemapSize = tilemapSize; }
	static glm::vec2 SetTilemapSize() { return m_Data.m_TilemapSize; }

	static void SetMines(unsigned int mines) { m_Data.m_Mines = mines; }
	static unsigned int GetMines() { return m_Data.m_Mines; }

	static unsigned int GetMaxTiles() { return m_Data.m_TilemapSize.x * m_Data.m_TilemapSize.y; }



private:

	static GameData m_Data;
	static Memory m_Instance;

	//static unsigned int m_Flags;
	//static unsigned int m_MaxSize;
	//static bool m_IsOnGame;
	//static glm::vec2 m_TilmapSize;
	//static float m_tileWidth;
	//static unsigned int m_Mines;
};