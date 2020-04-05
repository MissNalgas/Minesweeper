#include "Tilemap.h"
#include "Random.h"




Tilemap::Tilemap() : m_Camera(0,0,0,0)

{
	//m_MaxTiles = lines * rows;
	memory = new Memory;
	

	CreateCamera(1280.0f, 720.0f);

	
	Init();

	
}

bool Tilemap::Init()
{
	*memory = Memory::Get();
	if (!memory_allocated)
	{
		m_Tiles = new Tile[memory->GetMaxTiles()];
		memory_allocated = true;
	}
	else
	{
		delete[] m_Tiles;
		m_Tiles = new Tile[memory->GetMaxTiles()];
	}

	memory->SetFlag(0);
	int i = 0;
	for (int x = 0; x < memory->SetTilemapSize().x; x++)
	{
		for (int y = 0; y < memory->SetTilemapSize().y; y++)
		{
			m_Tiles[i] = Tile(x, y, i);
			//m_Tiles[i].SetState(States::Mined);
			i++;

		}
	}

	SetMines();

	memory->SetGame(1);
	return true;
	
}

Tilemap::~Tilemap()
{
	for (int x = 0; x < memory->GetMaxTiles(); x++)
	{
		std::cout << m_Tiles[x].String();
	}
	delete[] m_Tiles;
	delete memory;
}


void Tilemap::OnUpdate(Weasel::Timestep ts)
{

	//**************************

	m_Position = {10.0f, 10.0f, 0.0f};
	m_Size = {Memory::GetTileWidth() * 32.0f, Memory::GetTileWidth() * 16.0f };
	m_Color = { 0.3f, 0.3f, 0.3f, 1.0f };

	//**************************

	Weasel::RendererCommand::SetClearColor({ 0.3f, 0.3f, 0.3f, 1.0f });
	Weasel::RendererCommand::Clear();
	Weasel::Renderer2D::BeginScene(m_Camera);
	if (memory->GetGame())
	{
		if (memory->GetFlag() == memory->GetMines())
			std::cout << "Sweet Victory!\n";


		for (int i = 0; i < memory->GetMaxTiles(); i++)
		{
			m_Tiles[i].OnUpdate(m_Tiles);
			m_Tiles[i].Render(m_Position);
		}

		Weasel::Renderer2D::DrawQuad({ m_Position.x, m_Position.y, 0.0f }, m_Size, { 0.3f, 0.3f, 0.3f, 0.0f });


	}
	//Weasel::Renderer2D::DrawQuad(m_Position, m_Size, m_Color);
	Weasel::Renderer2D::EndScene();

}

void Tilemap::OnImGuiRender()
{
	for (int i = 0; i < memory->GetMaxTiles(); i++)
	{
		m_Tiles[i].OnImGuiRender();
	}
}


void Tilemap::SetMines()
{
	int i = 0;
	while (i < memory->GetMines())
	{
		Random::Init();
		int n = Random::Float() * memory->GetMaxTiles();
		if (!m_Tiles[n].IsMine())
		{
			m_Tiles[n].Mine();
			i++;
			int inicio1, fin1;
			int inicio2, fin2;
			
			Tile::Calculation(&inicio1, &fin1, m_Tiles[n].GetX(), memory->SetTilemapSize().x);
			Tile::Calculation(&inicio2, &fin2, m_Tiles[n].GetY(), memory->SetTilemapSize().y);

			
			for (int a = inicio1; a < fin1; a++)
			{
				for (int b = inicio2; b < fin2; b++)
				{
					int ptr = n + memory->SetTilemapSize().y * a;
					m_Tiles[ptr + b].AddMine();
				}
			}
		}
	}
}

void Tilemap::CreateCamera(float width, float height)
{

	float aspectRatio = (float)width / (float)height;

	float camWidth = 100.0f;
	float top = 0;
	float bottom = camWidth;
	float right = bottom * aspectRatio;
	float left = top * aspectRatio;
	m_Camera = Weasel::OrthographicCamera(left, right, bottom, top);

}

glm::vec2 Tilemap::ConvertCoord(float x, float y)
{
	float unitWidth = 100.0f / 720.0f;

	float xr = x * unitWidth;
	float yr = y * unitWidth;

	return glm::vec2(xr, yr);
}



void Tilemap::Click(Weasel::MouseButtonReleasedEvent& e)
{

	


	glm::vec2 position = ConvertCoord(Weasel::Input::GetMouseX(), Weasel::Input::GetMouseY());

	
	for (int i = 0; i < memory->GetMaxTiles(); i++)
	{
		if (m_Tiles[i].IsInCoord(position))
		{

			switch (e.GetMouseButton())
			{
			case 0:
			{
				m_Tiles[i].Clean();
			}
			break;
			case 1:
			{
				m_Tiles[i].Flag();
			}
			break;
			case 2:
			{
				Init();
			}
			break;

			}
			break;
			
		}
	}

	

}
