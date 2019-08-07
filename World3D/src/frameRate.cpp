#include "frameRate.h"

FrameRate::FrameRate()
	: deltaTime{ 0 }, m_oldTime{ (float)glfwGetTime() }, m_frameRateToKeep{ -1 }
{
}

// update deltaTime
// call keep_frame_rate function
void FrameRate::update()
{
	keep_frame_rate();

	float newTime = (float)glfwGetTime();
	deltaTime = newTime - m_oldTime;
	m_oldTime = newTime;
}

void FrameRate::show_frame_rate() const
{
	static int frames = 60;
	if (frames > 59)
	{
		frames = 0;
		std::cout << "Frame Rate = " << (1 / deltaTime) << std::endl;
	}
	frames++;
}

void FrameRate::set_frame_rate(float frameRateToKeep)
{
	if (frameRateToKeep > 0)
		m_frameRateToKeep = frameRateToKeep;
	else
		m_frameRateToKeep = -1.0f;
}

void FrameRate::keep_frame_rate() const
{
	if (m_frameRateToKeep == -1.0f) return;

	float realTime = (float)glfwGetTime();
	int timeToSleep = 0;
	while ( (realTime - m_oldTime) < (1 / m_frameRateToKeep) )
	{
		// sleep to save cpu
		// timeToSleep = 1000 * 75% * time left = 1000 * 0.8 * ( FrameTime - Elapsed time)
		// Obs - to keep the fps more stable, modify the value 75% to a lower one
		timeToSleep = (int)(750.0f * (1 / m_frameRateToKeep - realTime + m_oldTime));
		std::this_thread::sleep_for(std::chrono::milliseconds(timeToSleep));

		realTime = (float)glfwGetTime();
	}
}