#include "wspch.h"
#include "Texture.h"

#include "Weasel/Renderer/Renderer.h"
#include "Weasel/Platform/OpenGL/OpenGLTexture.h"

namespace Weasel {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WS_CORE_ASSERT(false, "RendererAPI: None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		WS_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WS_CORE_ASSERT(false, "RendererAPI: None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(width, height);
		}

		WS_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}
