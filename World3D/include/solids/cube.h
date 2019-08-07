#pragma once

namespace cube {

	static float vertices[] = {
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
	};

	static int indices[] = {
		// face +x
		4, 0, 3,
		3, 7, 4,
		// face -x
		5, 1, 2,
		2, 6, 5,
		// face +y
		5, 1, 0,
		0, 4, 5,
		// face -y
		6, 2, 3,
		3, 7, 6,
		// face +z
		0, 1, 2,
		2, 3, 0,
		// face -z
		4, 5, 6,
		6, 7, 4
	};

	static int const N_INDICES = 36;

	static int sizeof_vertices = sizeof(vertices);
	static int sizeof_indices = sizeof(indices);

	static void load() {}

}