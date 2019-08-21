#include "frameRate.h"

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