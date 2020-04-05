#include "wspch.h"
#include "Application.h"

#include "Weasel/Core/Log.h"


#include "Weasel/Renderer/Renderer.h"

#include "Input.h"
#include "GLFW/glfw3.h"


namespace Weasel {

	Application* Application::s_Instance = nullptr;

	Application::Application(const WindowProps& windowProps)
	{
		WS_PROFILE_FUNCTION();

		WS_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Scope<Window>(Window::Create(windowProps));
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);




	}

	void Application::OnEvent(Event& e)
	{
		WS_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose,this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowRisize, this, std::placeholders::_1));
		

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		}
	}


	void Application::Run() {

		WS_PROFILE_FUNCTION();

		while (m_Running) {
		
			WS_PROFILE_SCOPE("RunLoop");
		
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			
			if (!m_Minimized)
			{
				{
					WS_PROFILE_SCOPE("LayerStack OnUpdate");
		
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}
		
				m_ImGuiLayer->Begin();
				{
					WS_PROFILE_SCOPE("LayerStack OnImGuiRender");
					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
		
				}
		
		
				m_ImGuiLayer->End();
			}
		
		
		
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowRisize(WindowResizeEvent& e)
	{
		WS_PROFILE_FUNCTION();
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		
		return false;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		WS_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

}
