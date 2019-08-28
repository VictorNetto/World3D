#include "frameRate.h"

using namespace World3D;

FrameRate::FrameRate()
	: deltaTime{ 0 }, m_oldTime{ (float)glfwGetTime() }
{
}

// update deltaTime
void FrameRate::update()
{
	float newTime = (float)glfwGetTime();
	deltaTime = newTime - m_oldTime;
	m_oldTime = newTime;
}