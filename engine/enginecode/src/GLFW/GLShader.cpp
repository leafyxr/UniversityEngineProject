#include "engine_pch.h"
#include "GLFW\GLShader.h"
#include "glad\glad.h"
#include "systems\log.h"
#include <glm\gtc\type_ptr.hpp>

namespace Engine {

	static ShaderDataType GLSLStrToSDT(const std::string& glslSrc) {
		if (glslSrc == "bool")			return ShaderDataType::Bool;
		if (glslSrc == "int")			return ShaderDataType::Int;
		if (glslSrc == "ivec2")			return ShaderDataType::Int2;
		if (glslSrc == "ivec3")			return ShaderDataType::Int3;
		if (glslSrc == "ivec4")			return ShaderDataType::Int4;
		if (glslSrc == "float")			return ShaderDataType::Float;
		if (glslSrc == "vec2")			return ShaderDataType::Float2;
		if (glslSrc == "vec3")			return ShaderDataType::Float3;
		if (glslSrc == "vec4")			return ShaderDataType::Float4;
		if (glslSrc == "mat3")			return ShaderDataType::Mat3;
		if (glslSrc == "mat4")			return ShaderDataType::Mat4;
		if (glslSrc == "sampler2D")		return ShaderDataType::Sampler2D;
	}

	void GLShader::parseSource(const std::string & filepath)
	{
		std::fstream handle(filepath, std::ios::in);
		enum { NONE = -1, VERTEX, FRAGMENT, GEOMETRY, TESSCONTROL, TESSEVALUATION } region;
		if (!handle.is_open()) NG_ERROR("Could not open shader file '{}'.", filepath);

		std::string line, src[sizeof(region) + 1];

		bool geometry = false, tesselated = false;

		while (getline(handle, line)) {

			if (line.find("layout") != std::string::npos) {
				std::string word, type, name;
				std::istringstream iss(line);
				while (iss) {
					iss >> word;
					if (word == "out") { break; }
					if (word == "in") {
						iss >> type;
						iss >> name;
						name.pop_back();
						BufferElement element = BufferElement(GLSLStrToSDT(type), name, false);
						m_BufferLayout.addElement(element);
						break;
					}
				}
			}

			if (line.find("#region Vertex") != std::string::npos) { region = VERTEX; continue; }
			if (line.find("#region Fragment") != std::string::npos) { region = FRAGMENT; continue; }
			if (line.find("#region Geometry") != std::string::npos) { region = GEOMETRY; continue; }
			if (line.find("#region TessControl") != std::string::npos) { region = TESSCONTROL; continue; }
			if (line.find("#region TessEvaluation") != std::string::npos) { region = TESSEVALUATION; continue; }

			if (region != NONE) src[region] += (line + "\n");
		}
		handle.close();



		compileAndLink(src[VERTEX], src[FRAGMENT], src[GEOMETRY], src[TESSCONTROL], src[TESSEVALUATION]);
	}

	void GLShader::compileAndLink(std::string Vert, std::string Frag, std::string Geo, std::string TessControl, std::string TessEvaluation)
	{
		bool geoOn = true, tessOn = true;

		if (Geo == "")
		{
			NG_INFO("No Geometry Shader");
			geoOn = false;
		}
		if (TessControl == "" || TessEvaluation == "")
		{
			NG_INFO("No Tesselation Shader");
			tessOn = false;
		}

		GLuint GeometryShader, TessControlShader, TessEvaluationShader;

		GLuint VertShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* source = Vert.c_str();
		glShaderSource(VertShader, 1, &source, 0);
		glCompileShader(VertShader);
		GLint isCompiled = 0;
		glGetShaderiv(VertShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(VertShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(VertShader, maxLength, &maxLength, &infoLog[0]);
			NG_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(VertShader);
			return;
		}

		GLuint FragShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = Frag.c_str();
		glShaderSource(FragShader, 1, &source, 0);
		glCompileShader(FragShader);

		glGetShaderiv(FragShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(FragShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(FragShader, maxLength, &maxLength, &infoLog[0]);
			NG_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(FragShader);
			glDeleteShader(VertShader);

			return;
		}

		if (geoOn)
		{
			GeometryShader = glCreateShader(GL_GEOMETRY_SHADER);

			source = Geo.c_str();
			glShaderSource(GeometryShader, 1, &source, 0);
			glCompileShader(GeometryShader);

			glGetShaderiv(GeometryShader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(GeometryShader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(GeometryShader, maxLength, &maxLength, &infoLog[0]);
				NG_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

				glDeleteShader(FragShader);
				glDeleteShader(VertShader);
				glDeleteShader(GeometryShader);

				return;
			}
		}

		if (tessOn)
		{
			TessControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);

			source = TessControl.c_str();
			glShaderSource(TessControlShader, 1, &source, 0);
			glCompileShader(TessControlShader);

			glGetShaderiv(TessControlShader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(TessControlShader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(TessControlShader, maxLength, &maxLength, &infoLog[0]);
				NG_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

				glDeleteShader(FragShader);
				glDeleteShader(VertShader);
				glDeleteShader(GeometryShader);
				glDeleteShader(TessControlShader);

				return;
			}

			TessEvaluationShader = glCreateShader(GL_TESS_EVALUATION_SHADER);

			source = TessEvaluation.c_str();
			glShaderSource(TessEvaluationShader, 1, &source, 0);
			glCompileShader(TessEvaluationShader);

			glGetShaderiv(TessEvaluationShader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(TessEvaluationShader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(TessEvaluationShader, maxLength, &maxLength, &infoLog[0]);
				NG_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

				glDeleteShader(FragShader);
				glDeleteShader(VertShader);
				glDeleteShader(GeometryShader);
				glDeleteShader(TessControlShader);
				glDeleteShader(TessEvaluationShader);

				return;
			}
		}

		m_isTesselated = tessOn;

		GLuint program = glCreateProgram();
		glAttachShader(program, VertShader);
		glAttachShader(program, FragShader);
		if (geoOn) glAttachShader(program, GeometryShader);
		if (tessOn) {
			glAttachShader(program, TessControlShader);
			glAttachShader(program, TessEvaluationShader);
		}
		glLinkProgram(program);

		m_RendererID = program;

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			NG_ERROR("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(program);
			glDeleteShader(FragShader);
			glDeleteShader(VertShader);
			if (geoOn) glDeleteShader(GeometryShader);
			if (tessOn) {
				glDeleteShader(TessControlShader);
				glDeleteShader(TessEvaluationShader);
			}
			return;
		}

		glDetachShader(program, VertShader);
		glDetachShader(program, FragShader);
		if (geoOn) glDetachShader(program, GeometryShader);
		if (tessOn) {
			glDetachShader(program, TessControlShader);
			glDetachShader(program, TessEvaluationShader);
		}
#
	}

	GLShader::GLShader(const std::string & filepath)
	{
		parseSource(filepath);
	}

	GLShader::GLShader(const std::string & VertFilepath, const std::string & FragFilepath)
	{
		std::fstream handleVert(VertFilepath, std::ios::in);
		enum { NONE = -1, VERTEX, FRAGMENT, GEOMETRY, TESSCONTROL, TESSEVALUATION } region;
		if (!handleVert.is_open()) NG_ERROR("Could not open shader file '{}'.", VertFilepath);

		std::string line, src[sizeof(region) + 1];

		while (getline(handleVert, line)) {

			if (line.find("layout") != std::string::npos) {
				std::string word, type, name;
				std::istringstream iss(line);
				while (iss) {
					iss >> word;
					if (word == "out") { break; }
					if (word == "in") {
						iss >> type;
						iss >> name;
						name.pop_back();
						BufferElement element = BufferElement(GLSLStrToSDT(type), name, false);
						m_BufferLayout.addElement(element);
						break;
					}
				}
			}
			src[VERTEX] += (line + "\n");
		}

		std::fstream handleFrag(FragFilepath, std::ios::in);
		if (!handleFrag.is_open()) NG_ERROR("Could not open shader file '{}'.", FragFilepath);

		while (getline(handleFrag, line)) {

			if (line.find("layout") != std::string::npos) {
				std::string word, type, name;
				std::istringstream iss(line);
				while (iss) {
					iss >> word;
					if (word == "out") { break; }
					if (word == "in") {
						iss >> type;
						iss >> name;
						name.pop_back();
						BufferElement element = BufferElement(GLSLStrToSDT(type), name, false);
						m_BufferLayout.addElement(element);
						break;
					}
				}
			}
			src[FRAGMENT] += (line + "\n");
		}

		handleVert.close();
		compileAndLink(src[VERTEX], src[FRAGMENT], src[GEOMETRY], src[TESSCONTROL], src[TESSEVALUATION]);
	}

	void GLShader::bind()
	{
		glUseProgram(m_RendererID);
	}

	void GLShader::unbind()
	{
		glUseProgram(0);
	}

	bool GLShader::uploadData(const std::string & name, void * data)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		GLenum Type;
		GLint size;
		GLchar Name[16];
		GLsizei length;
		glGetActiveUniform(m_RendererID, location, 16, &length, &size, &Type, Name);

		const float * addrf;
		const int * addri;
		GLint valueInt;
		GLfloat valueFloat;

		m_UniformLayout[Name] = data;

		switch (Type)
		{
		case GL_FLOAT_MAT4:
			addrf = static_cast<float*>(data);
			glUniformMatrix4fv(location, 1, GL_FALSE, addrf);
			return true;
			break;
		case GL_FLOAT_MAT3:
			addrf = static_cast<float*>(data);
			glUniformMatrix3fv(location, 1, GL_FALSE, addrf);
			return true;
			break;
		case GL_FLOAT_VEC4:
			addrf = static_cast<const float*>(data);
			glUniform4fv(location, 1, addrf);
			return true;
			break;
		case GL_FLOAT_VEC3:
			addrf = static_cast<const float*>(data);
			glUniform3fv(location, 1, addrf);
			return true;
			break;
		case GL_FLOAT_VEC2:
			addrf = static_cast<const float*>(data);
			glUniform2fv(location, 1, addrf);
			return true;
			break;
		case GL_FLOAT:
			valueFloat = *static_cast<float*>(data);
			glUniform1f(location, valueFloat);
			return true;
			break;
		case GL_INT:
			valueInt = *static_cast<int*>(data);
			glUniform1i(location, valueInt);
			return true;
			break;
		case GL_SAMPLER_2D:
			valueInt = *static_cast<int*>(data);
			glUniform1i(location, valueInt);
			return true;
			break;
		default:
			NG_ERROR("(ID = {0}) Invalid Type, Name = {1}, (Type ID = {2})", m_RendererID, name, Type);
			break;
		}
		return false;
	}

	bool GLShader::uploadData(const UniformLayout & uniforms)
	{
		for (auto dataPair : uniforms) {
			uploadData(dataPair.first, dataPair.second);
		}
		return true;
	}
	void GLShader::uploadInt(const std::string & name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}
	void GLShader::uploadFloat(const std::string & name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}
	void GLShader::uploadFloat2(const std::string & name, const glm::vec2 & value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2i(location, value.x, value.y);
	}
	void GLShader::uploadFloat3(const std::string & name, const glm::vec3 & value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}
	void GLShader::uploadFloat4(const std::string & name, const glm::vec4 & value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
	void GLShader::uploadMat3(const std::string & name, const glm::mat3 & matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void GLShader::uploadMat4(const std::string & name, const glm::mat4 & matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	bool GLShader::isTesselated()
	{
		return m_isTesselated;
	}

}