#pragma once
#include "glm/glm.hpp"
#include "Material.h"

namespace Engine {
	class Text {
	private:
		static bool s_Init;

	public:
		virtual void setText(std::string& text) = 0;
		virtual void setPosition(glm::vec2 pos) = 0;
		virtual void setPosX(float x) = 0;
		virtual void setPosY(float y) = 0;
		virtual void setScale(float scale) = 0;
		virtual void setColour(glm::vec3 colour) = 0;

		virtual inline std::string getText() = 0;
		virtual inline glm::vec2 getPosition() = 0;
		virtual inline float getPosX() = 0;
		virtual inline float getPosY() = 0;
		virtual inline float getScale() = 0;
		virtual inline glm::vec3 getColour() = 0;

		virtual void render(std::shared_ptr<Material> mat) = 0;

		static Text *create(const std::string& filepath);
	};
	class Character {
	private:
		glm::vec2 m_startUV;
		glm::vec2 m_endUV;
		glm::ivec2 m_size;
		glm::ivec2 m_bearing;
		int m_advance;
	public:
		Character() {} //!<Default Constructor
		Character(glm::ivec2 size, glm::ivec2 bearing, glm::ivec2 startUV = glm::vec2(0.0f, 0.0f), glm::ivec2 endUV = glm::vec2(1.0, 1.0), int advance = 1) :
			m_size(size), m_bearing(bearing), m_startUV(startUV), m_endUV(endUV), m_advance(advance) {}
		void setUVs(glm::vec2 startUV, glm::vec2 endUV) { m_startUV = startUV; m_endUV = endUV; }
		inline glm::vec2 getStartUV() { return m_startUV; }
		inline glm::vec2 getEndUV() { return m_endUV; }
		inline glm::ivec2 getSize() { return m_size; }
		inline glm::ivec2 getBearing() { return m_bearing; }
		inline int getAdvance() { return m_advance; }
	};


}