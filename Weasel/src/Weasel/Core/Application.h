#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Weasel/Events/Events.h"
#include "Weasel/Events/ApplicationEvent.h"

#include "Weasel/ImGui/ImGuiLayer.h"

#include "Weasel/Core/Timestep.h"

namespace Weasel {

	class WS_API Application
	{
	public:
		Application(const WindowProps& windowProps = WindowProps::WindowProps());
		virtual ~Application() {}

		void OnEvent(Event& e);

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);


		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowRisize(WindowResizeEvent& e);

		void LayerPrint();
		void ImGuiRender();
		void OnUpdate();

	private:

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:

		static Application* s_Instance;

	};

	Application* CreateApplication();

}

