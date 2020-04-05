#include "Tile.h"

#include <sstream>
#include "Weasel.h"
#include "imgui.h"
#include "Memory.h"


Tile::Tile(unsigned int x, unsigned int y, unsigned int n) : m_X(x), m_Y(y), m_N(n)
{
	m_State = States::Unmined;
	m_HasMine = false;
	m_Color = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_Position = { 0.0f, 0.0f };
	m_Size = { 0.0f, 0.0f };
	m_MinesNearby = 0;
}

Tile::~Tile()
{
	
}

void Tile::OnUpdate(Tile* tiles)
{
	UpdateColor();
	ZeroClean(tiles);
}

void Tile::OnImGuiRender()
{
	auto pos = ImGui::GetWindowPos();
	pos.x += m_Position.x*7.2f;
	pos.y += m_Position.y*7.2f;
	pos.x -= 50.0f;
	pos.y -= 50.0f;
	
	int i = m_MinesNearby + 48;
	char buffer = *(char*)(void*)&i;

	if (m_State == States::Mined && !m_HasMine && m_MinesNearby != 0)
		ImGui::GetForegroundDrawList()->AddText(pos, 0xFF1212FF, &buffer, &buffer+1);
}

void Tile::Render(glm::vec3 position)
{

	m_Position = { (m_X * Memory::GetTileWidth()) + 1.0f + position.x, (m_Y * Memory::GetTileWidth()) + 1.0f + position.y };
	m_Size = { Memory::GetTileWidth() - 1, Memory::GetTileWidth() - 1 };


	if (m_HasMine && m_State == States::Mined)
	{
		Weasel::Renderer2D::DrawQuad(m_Position, m_Size, { 0.8f, 0.2f, 0.3f, 1.0f });
	}
	
	Weasel::Renderer2D::DrawQuad(m_Position, m_Size , m_Color);

	//Weasel::Renderer2D::DrawQuad({ 10.0f, 20.0f }, { 100.0f, 100.0f }, { 0.2f, 0.3f, 0.8f, 1.0f });


}


bool Tile::IsInCoord(glm::vec2 pos)
{
	if (pos.x >= m_Position.x && pos.x <= (float)m_Position.x + (float)Memory::GetTileWidth())
		if (pos.y >= m_Position.y && pos.y <= (float)m_Position.y + (float)Memory::GetTileWidth())
		{
			return true;
		}
	return false;
}


void Tile::Calculation(int* inicio, int* fin, int x, int rows)
{
	if (x == 0) {
		*inicio = 0;
	}
	else {
		*inicio = -1;
	}
	if (x == rows - 1)
	{
		*fin = 1;
	}
	else {
		*fin = 2;
	}
}


void Tile::Clean()
{
	if (m_State == States::Unmined)
		m_State = States::Mined;
}

void Tile::ZeroClean(Tile* tilemap)
{
	int inicio1, fin1;
	int inicio2, fin2;

	Calculation(&inicio1, &fin1, m_X, Memory::SetTilemapSize().x);
	Calculation(&inicio2, &fin2, m_Y, Memory::SetTilemapSize().y);


	for (int a = inicio1; a < fin1; a++)
		for (int b = inicio2; b < fin2; b++)
		{
			int ptr = m_N + Memory::SetTilemapSize().y * a;
			if (tilemap[ptr + b].GetState() == States::Mined && tilemap[ptr + b].GetValue() == 0 && !m_HasMine)
			{
				Tile tile1 = tilemap[ptr + b];
				m_State = States::Mined;
			}
		}
}

void Tile::Flag()
{
	switch (m_State)
	{
	case States::Mined:

		break;
	case States::Flag:
	{
		m_State = States::Unmined;
		Memory::RemoveFlag();
	}
		break;
	case States::Unmined:
		m_State = States::Flag;
		Memory::AddFlag();
		break;
	}
}

std::string Tile::String()
{
	std::stringstream ss;
	if (m_HasMine)
		ss << "State: " << "Does" << " x: " << m_X << " y: " << m_Y << " State: " << GetState(m_State) << "value: " << m_MinesNearby << "\n";
	else
		ss << "State: " << "Doesnt" << " x: " << m_X << " y: " << m_Y << " State: " << GetState(m_State) << "value: " << m_MinesNearby << "\n";

	return ss.str();
	
}

bool Tile::Mine()
{
	if (!m_HasMine)
	{
		m_HasMine = true;
		return true;
	}
	return false;
}

void Tile::UpdateColor()
{
	switch(m_State)
	{
		//case States::Unmined: m_Color = { 0.1f, 0.8f, 0.2f, 1.0f };
		case States::Unmined: m_Color = { 0.2f, 0.3f, 0.8f, 1.0f }; break;
		case States::Mined: m_Color = { 1.0f, 1.0f, 1.0f, 1.0f }; break;
		case States::Flag: m_Color = { 0.2f,0.8f,0.3f,1.0f }; break;
	}
}


