/** \file graphicsContext
*/

#pragma once

/**
\class Interface class for all graphics contexts. Will combine windows tech with graphics API i.e. OPENGLGLFW or WIN32DIRECTX
* Basically provides means for initialisation and swapchain implementation.
*/

class GraphicsContext
{
public:
	//! Initialise
	virtual void init() = 0;
	//! Swap GPU Buffers
	virtual void swapBuffers() = 0;
};