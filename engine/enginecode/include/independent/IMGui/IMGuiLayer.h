#pragma once

#include "Renderer/Layer.h"

namespace Engine {
	class IMGuiLayer : public Layer
	{
	public:
		IMGuiLayer();
		~IMGuiLayer();

		void onAttach() override;


		void onDetach() override;


		void onUpdate(float timestep) override;


		void onEvent(Event& event) override;

	private:

	};
}