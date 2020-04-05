#pragma once
#include "Weasel/Renderer/GraphicsContext.h"


struct GLFWwindow;

namespace Weasel {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowhandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;

	};

}