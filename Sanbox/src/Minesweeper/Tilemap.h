#pragma once
#include "Tile.h"
#include <Weasel.h>
#include "memory.h"

class Tilemap
{
public:
	Tilemap();
	~Tilemap();

	void OnUpdate(Weasel::Timestep ts);

	void OnImGuiRender();

	bool Init();

	void Click(Weasel::MouseButtonReleasedEvent& e);

	glm::vec2 GetPosition() { return m_Position; }


private:


	void SetMines();

	void CreateCamera(float width, float height);

	glm::vec2 ConvertCoord(float x, float y);


private:

	Tile* m_Tiles;

	Weasel::OrthographicCamera m_Camera;

	glm::vec3 m_Position;
	glm::vec2 m_Size;
	glm::vec4 m_Color;

	Tile** m_TilesToClean;

	Memory* memory;
	bool memory_allocated = false;
};
