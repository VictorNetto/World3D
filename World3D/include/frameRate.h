#pragma once

#include <iostream>
#include <chrono>
#include <thread>

#include <GLFW/glfw3.h>

namespace World3D {

	class FrameRate
	{
	public:
		FrameRate();

		void update();

		float deltaTime;  // seconds

	private:
		float m_oldTime;
	};

}