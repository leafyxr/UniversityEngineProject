/** \file Layer.h
*/
#pragma once
#include "systems\system.h"
#include "Renderer.h"
#include "Camera.h"
#include <vector>

namespace Engine {
	/**
	\class Layer
	Base Layer Class
	*/
	class Layer {
	protected:
		std::string m_name;
		std::shared_ptr<Renderer> m_renderer;
		std::shared_ptr<CameraController> m_camera;
	public:
		Layer(const std::string& name = "Layer") { m_name = name; }
		virtual ~Layer() {}

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(float timestep) {}
		virtual void onEvent(Event& event) {}
		virtual void onImGuiRender() {}

		inline const std::string& getName() { return m_name; }
	};

	/**
	\class LayerStack
	Stores and manages active Layers
	*/
	class Layerstack : public System {
	private:
		unsigned int m_LayerInsertIndex = 0;//!<Layer index
		std::vector<Layer*> m_layer;//!<vector storing active layers
	public:
		void start(SystemSignal init = SystemSignal::None, ...) override;
		void stop(SystemSignal init = SystemSignal::None, ...) override;
		void push(Layer* layer);
		void pop();

		std::vector<Layer*>::iterator begin() { return m_layer.begin(); }
		std::vector<Layer*>::iterator end() { return m_layer.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_layer.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_layer.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return m_layer.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return m_layer.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_layer.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_layer.rend(); }
	};
}