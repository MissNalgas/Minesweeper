#include "wspch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Weasel/Platform/OpenGL/OpenGLBuffer.h"

namespace Weasel {
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WS_CORE_ASSERT(false, "RendererAPI:None is not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(size);
		}

		WS_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WS_CORE_ASSERT(false, "RendererAPI:None is not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		WS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WS_CORE_ASSERT(false, "RendererAPI:None is not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}

		WS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}