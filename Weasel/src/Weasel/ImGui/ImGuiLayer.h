#pragma once

#include "Weasel/Core/Layer.h"
#include "Weasel/Core/Core.h"
#include "Weasel/Events/MouseEvent.h"
#include "Weasel/Events/KeyEvent.h"
#include "Weasel/Events/ApplicationEvent.h"

namespace Weasel {

	class WS_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();


	private:
		float m_Time = 0.0f;

	};

}
