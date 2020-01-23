#pragma once
#include <gtest\gtest.h>
#include "Renderer\Camera.h"
#include <memory>

float left, right, top, bottom = 1;
float Fov, aspRatio, near, far = 1;

std::shared_ptr<Engine::FreeOrthoCameraController2D> OrthoController;
std::shared_ptr<Engine::FPSCameraControllerEuler> EulerController;