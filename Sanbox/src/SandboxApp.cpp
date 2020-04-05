#include <Weasel.h>
//******************Entry Point
#include <Weasel/Core/EntryPoint.h>


#include "Weasel/Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include "Minesweeper/GameLayer.h"




class SandboxApp : public Weasel::Application {

public:


	SandboxApp(const Weasel::WindowProps& windowProps) : Application(windowProps)
	{

		Application::PushLayer(new GameLayer());
	}

	~SandboxApp()
	{

	}
};

Weasel::Application* Weasel::CreateApplication() {

	Weasel::WindowProps wp = Weasel::WindowProps::WindowProps();
	wp.Title = "Minesweeper";

	return new SandboxApp(wp);

}