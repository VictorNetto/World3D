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
		void clear_buffers() const;
		void draw() const;
		void swap_buffers() const;
		float delta_time() const;

	private:
		static FrameRate m_frameRate;
		static Camera m_camera;
		GLFWwindow* m_window;

		// objects stuff ----------------------------------------------------------
		// ------------------------------------------------------------------------
	public:
		void attach_object(Object* object);
	private:
		std::vector<Object*> m_attachedObjects;

		// light/shader stuff -----------------------------------------------------
		// ------------------------------------------------------------------------
	public:
		void install_light(Light* light);
	private:
		std::vector<Light*> m_installedLights;  // Lights used in the World that
		                                        // will be updated every frame
		void update_uniforms();
		// callback functions -----------------------------------------------------
		// ------------------------------------------------------------------------
	private:
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};

}