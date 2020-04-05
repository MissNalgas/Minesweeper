#include "wspch.h"
#include "OpenGLContext.h"
#include "GLFW/glfw3.h"
#include "GLAD/glad.h"


namespace Weasel {

	OpenGLContext::OpenGLContext(GLFWwindow* windowhandle) : m_WindowHandle(windowhandle)
	{
		WS_CORE_ASSERT(windowhandle, "Window Handle!!");
	}

	void OpenGLContext::Init()
	{
		WS_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		WS_CORE_ASSERT(status, "Failed to initialize Glad!");

		WS_CORE_INFO("OpenGL Renderer: {0}, {1}, {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));

	}
	
	void OpenGLContext::SwapBuffers()
	{
		WS_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}

}