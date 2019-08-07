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
	void show_frame_rate() const;
	void set_frame_rate(float frameRateToKeep);

	float deltaTime;  // seconds

private:
	float m_oldTime;
	float m_frameRateToKeep;  // -1 for ilimited frame rate

	void keep_frame_rate() const;
};