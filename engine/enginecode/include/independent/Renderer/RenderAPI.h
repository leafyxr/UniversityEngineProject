/** \file RenderAPI.h
*/
#pragma once

namespace Engine {

	/**
	\class RenderAPI
	Manages current API in Use
	*/
	class RenderAPI {
	public:
		enum class API {
			None = 0, OpenGL = 1, Direct3D = 2
		};
		//! get api
		/*!
		\return active API
		*/
		static API getApi() { return s_Api; };
	private:
		static API s_Api;//!<Current API
	};

}