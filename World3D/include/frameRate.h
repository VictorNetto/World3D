#pragma once

#include <iostream>
#include <chrono>
#include <thread>

#include <GLFW/glfw3.h>

class FrameRate
{
public:
	FrameRate();

	void update();

	float deltaTime;  // seconds

private:
	float m_oldTime;
};