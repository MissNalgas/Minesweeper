#pragma once
#include <iostream>
#include <Weasel.h>

static enum class States
{
	Unmined, Mined, Flag
};

class Tile
{
public:

	Tile(unsigned int x = 0, unsigned int y = 0, unsigned int n = 0);
	~Tile();

	void OnUpdate(Tile* tiles);
	void OnImGuiRender();

	void Render(glm::vec3 position);

	unsigned int GetX() { return m_X; }
	unsigned int GetY() { return m_Y; }

	States GetState() { return m_State; }
	void SetState(States state) { m_State = state; }

	glm::vec2 GetPosition() { return m_Position; }
	glm::vec2 GetSize() { return m_Size; }

	

	void SetValue(int value) { m_MinesNearby = value; }
	int GetValue() { return m_MinesNearby; }
	void AddMine() { m_MinesNearby++; }
	bool IsMine() { return m_HasMine; }
	bool IsInCoord(glm::vec2 position);

	void Clean();
	void ZeroClean(Tile* tilemap);
	void Flag();

	static void Calculation(int* inicio, int* fin, int x, int rows);

	std::string String();
	

	bool Mine();

private:


	std::string GetState(const States& state) { if (state == States::Mined) return "MINED"; else return "UNMINED"; }

	void UpdateColor();

private:
	unsigned int m_N;
	States m_State;
	bool m_HasMine;

	unsigned int m_X, m_Y;

	glm::vec4 m_Color;
	glm::vec2 m_Position;
	glm::vec2 m_Size;
	unsigned int m_MinesNearby;

};
