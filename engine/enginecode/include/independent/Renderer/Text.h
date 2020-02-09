#pragma once
#include <glm\glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Engine {

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