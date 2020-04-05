#include "wspch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Weasel/Platform/OpenGL/OpenGLVertexArray.h"

namespace Weasel {

	Ref<VertexArray> VertexArray::Create()
	{
		WS_PROFILE_FUNCTION();

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WS_CORE_ASSERT(false, "RendererAPI: None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
		}

		WS_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}