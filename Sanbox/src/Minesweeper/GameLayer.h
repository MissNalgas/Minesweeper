#pragma once
#include "Weasel.h"
#include "Tilemap.h"
#include "Memory.h"

class GameLayer : public Weasel::Layer
{

public:
	GameLayer();
	~GameLayer();

	virtual void OnUpdate(Weasel::Timestep ts) override;
	virtual void OnEvent(Weasel::Event& e) override;

	virtual void OnImGuiRender() override;


	bool OnClickEvent(Weasel::MouseButtonReleasedEvent& event);
private:

	Tilemap* m_Tilemap;

	GameData data;

};
