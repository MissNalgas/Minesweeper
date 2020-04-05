#include "wspch.h"
#include "RendererCommand.h"

#include "Weasel/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Weasel {

	RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;


}