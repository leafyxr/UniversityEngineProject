/** \file IMGuiLayer.h
*/

#pragma once

#include "Renderer/Layer.h"

#include "events/KeyEvents.h"
#include "events/MouseEvents.h"
#include "events/WindowEvents.h"

namespace Engine {
	/**
	\class IMGui Layer
	Handles any IMGui required functionality
	*/
	class IMGuiLayerGLFW : public Layer
	{
	public:
		IMGuiLayerGLFW();
		~IMGuiLayerGLFW();

		virtual void onAttach() override;


		virtual void onDetach() override;


		virtual void onUpdate(float timestep) override;

		void Begin();

		void End();

		void onImGuiRender() override;

	private:
	};
}