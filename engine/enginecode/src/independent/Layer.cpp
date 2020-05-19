#include "engine_pch.h"
#include "Renderer\Layer.h"
#include "systems\log.h"

namespace Engine {


	void Layerstack::start(SystemSignal init, ...)
	{
	}

	void Layerstack::stop(SystemSignal init, ...)
	{
		for (Layer* layer : m_layer)
			delete layer;
	}

	void Layerstack::push(Layer* layer)
	{
		if (m_LayerInsertIndex == 0) {
			std::vector<Layer*> layers = { layer };
			m_layer = layers;
			m_LayerInsertIndex++;
			return;
		}
			m_layer.emplace(m_layer.begin() + m_LayerInsertIndex, layer);
			m_LayerInsertIndex++;
	}

	void Layerstack::pop()
	{
		m_layer.pop_back();
	}

}