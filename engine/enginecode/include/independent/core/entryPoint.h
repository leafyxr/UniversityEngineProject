/** \file entryPoint.h
*/
#pragma once

#include "core/application.h"
#ifdef NG_PLATFORM_WINDOWS

extern Engine::Application* Engine::startApplication();

int main(int argc, char** argv)
{
	auto application = Engine::startApplication();
	application->run();
	delete application;

	return 0;
}

#endif

