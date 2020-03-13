#pragma once

#include "Renderer/Layer.h"

namespace Engine {
	class IMGuiLayer : public Layer
	{
	public:
		IMGuiLayer();
		~IMGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:

	};
}