#pragma once
#include <gtest/gtest.h>

#include "events\Event.h"
#include "events\WindowEvents.h"

const int width = 1024;
const int height = 720;

const int xPos = 100;
const int yPos = 100;

Engine::WindowResizeEvent re(width, height);
Engine::WindowCloseEvent ce;
Engine::WindowFocusEvent fe(xPos,yPos);

bool OnResizeTrue(Engine::WindowResizeEvent& e) {
	return true;
}

bool OnResizeFalse(Engine::WindowResizeEvent& e) {
	return false;
}

bool onClose(Engine::WindowCloseEvent& e) {
	return true;
}

bool onFocusTrue(Engine::WindowFocusEvent& e)
{
	return true;
}

bool onFocusFalse(Engine::WindowFocusEvent& e)
{
	return false;
}