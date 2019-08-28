#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "object.h"
#include "frameRate.h"
#include "camera.h"
#include "light.h"


namespace World3D {

	/*
		A class that handles Objects in the World3D:
			Objects, Lights, Cameras

		Also handles GLFW related things such as GLFWwindow
		and callback functions
	*/
	class World
	{
		// World3D is a Singleton
	public:
		static World& get_instance();
		World(World const&) = delete;
		void operator=(World const&) = delete;
	private:
		World();
		~World();

	public:

		bool should_close() const;
		void update();
		void clear() const;
		void draw() const;
		void swap_buffers() const;
		float delta_time() const;

		bool floorVisible = true;

	private:
		static FrameRate m_frameRate;
		static Camera m_camera;
		GLFWwindow* m_window;

		// light/shader stuff -----------------------------------------------------
		// ------------------------------------------------------------------------
	private:
		static void update_uniforms();

		// callback functions -----------------------------------------------------
		// ------------------------------------------------------------------------
	private:
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};

}