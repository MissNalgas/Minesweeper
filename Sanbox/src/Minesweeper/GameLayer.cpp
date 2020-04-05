#include "GameLayer.h"

#include "imgui.h"

//void* operator new(size_t size) {
//	std::cout << "Allocate" << size << " Bytes.\n";
//	return malloc(size);
//}


GameLayer::GameLayer() : Layer("MineSweeper")
{
	
	
	data.m_TilemapSize = { 10, 10 };
	data.m_Mines = 15;
	
	Memory::SetData(data);

	m_Tilemap = new Tilemap();


}

GameLayer::~GameLayer()
{
	delete m_Tilemap;
}

void GameLayer::OnUpdate(Weasel::Timestep ts)
{
	
	m_Tilemap->OnUpdate(ts);

}

void GameLayer::OnEvent(Weasel::Event& e)
{
	Weasel::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Weasel::MouseButtonReleasedEvent>(std::bind(&GameLayer::OnClickEvent, this, std::placeholders::_1));
}

void GameLayer::OnImGuiRender()
{
	ImGui::Begin("Custom tilemap");

	ImGui::InputFloat("X size", &data.m_TilemapSize.x, 1.0f, 1.0f, 1.0f);
	ImGui::InputFloat("Y size", &data.m_TilemapSize.y, 1.0f, 1.0f, 1.0f);
	ImGui::InputInt("Mines", (int*)&data.m_Mines);

	ImGui::End();
	m_Tilemap->OnImGuiRender();
}

bool GameLayer::OnClickEvent(Weasel::MouseButtonReleasedEvent& event)
{
	if (event.GetMouseButton() == 2)
		Memory::SetData(data);
	m_Tilemap->Click(event);
	return false;
}
