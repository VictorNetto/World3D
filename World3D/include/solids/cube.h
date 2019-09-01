#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace VertexData {

	namespace cube {

		static const int N_INDICES = 36;
		static const int N_VERTICES = 36;

		static float basic_vertices[3 * N_VERTICES] = {
			// +Z
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			 0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,

			 // -Z
			  0.5f,  0.5f, -0.5f,
			 -0.5f,  0.5f, -0.5f,
			 -0.5f, -0.5f, -0.5f,

			  0.5f,  0.5f, -0.5f,
			 -0.5f, -0.5f, -0.5f,
			  0.5f, -0.5f, -0.5f,

			  // +Y
			   0.5f,  0.5f, -0.5f,
			  -0.5f,  0.5f, -0.5f,
			  -0.5f,  0.5f,  0.5f,

			   0.5f,  0.5f, -0.5f,
			  -0.5f,  0.5f,  0.5f,
			   0.5f,  0.5f,  0.5f,

			   // -Y
				0.5f, -0.5f, -0.5f,
			   -0.5f, -0.5f, -0.5f,
			   -0.5f, -0.5f,  0.5f,

				0.5f, -0.5f, -0.5f,
			   -0.5f, -0.5f,  0.5f,
				0.5f, -0.5f,  0.5f,

				// +X
				 0.5f,  0.5f, -0.5f,
				 0.5f,  0.5f,  0.5f,
				 0.5f, -0.5f,  0.5f,

				 0.5f,  0.5f, -0.5f,
				 0.5f, -0.5f,  0.5f,
				 0.5f, -0.5f, -0.5f,

				 // -X
				 -0.5f,  0.5f, -0.5f,
				 -0.5f,  0.5f,  0.5f,
				 -0.5f, -0.5f,  0.5f,

				 -0.5f,  0.5f, -0.5f,
				 -0.5f, -0.5f,  0.5f,
				 -0.5f, -0.5f, -0.5f
		};

		static float basic_normals[3 * N_VERTICES] = {
			// +Z
			 0.0f,  0.0f,  1.0f,
			 0.0f,  0.0f,  1.0f,
			 0.0f,  0.0f,  1.0f,
			 0.0f,  0.0f,  1.0f,
			 0.0f,  0.0f,  1.0f,
			 0.0f,  0.0f,  1.0f,


			 // -Z
			  0.0f,  0.0f, -1.0f,
			  0.0f,  0.0f, -1.0f,
			  0.0f,  0.0f, -1.0f,
			  0.0f,  0.0f, -1.0f,
			  0.0f,  0.0f, -1.0f,
			  0.0f,  0.0f, -1.0f,

			  // +Y
			   0.0f,  1.0f,  0.0f,
			   0.0f,  1.0f,  0.0f,
			   0.0f,  1.0f,  0.0f,
			   0.0f,  1.0f,  0.0f,
			   0.0f,  1.0f,  0.0f,
			   0.0f,  1.0f,  0.0f,

			   // -Y
				0.0f, -1.0f,  0.0f,
				0.0f, -1.0f,  0.0f,
				0.0f, -1.0f,  0.0f,
				0.0f, -1.0f,  0.0f,
				0.0f, -1.0f,  0.0f,
				0.0f, -1.0f,  0.0f,

				// +X
				 1.0f,  0.0f,  0.0f,
				 1.0f,  0.0f,  0.0f,
				 1.0f,  0.0f,  0.0f,
				 1.0f,  0.0f,  0.0f,
				 1.0f,  0.0f,  0.0f,
				 1.0f,  0.0f,  0.0f,

				 // -X
				 -1.0f,  0.0f,  0.0f,
				 -1.0f,  0.0f,  0.0f,
				 -1.0f,  0.0f,  0.0f,
				 -1.0f,  0.0f,  0.0f,
				 -1.0f,  0.0f,  0.0f,
				 -1.0f,  0.0f,  0.0f
		};

		static float vertices[3 * N_VERTICES];

		static float normals[3 * N_VERTICES];

		static float textCoordinates[] = {
			// +Z
			4.0f, 0.0f,
			4.0f, 4.0f,
			0.0f, 4.0f,

			4.0f, 0.0f,
			0.0f, 4.0f,
			0.0f, 0.0f,

			//--------
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			1.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,

			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			1.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,

			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			1.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,

			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			1.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,

			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			1.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f
		};

		static int indices[] = {
			 0,  1,  2,
			 3,  4,  5,

			 6,  7,  8,
			 9, 10, 11,

			12, 13, 14,
			15, 16, 17,

			18, 19, 20,
			21, 22, 23,

			24, 25, 26,
			27, 28, 29,

			30, 31, 32,
			33, 34, 35
		};

		static int sizeof_vertices = sizeof(vertices);
		static int sizeof_normals = sizeof(normals);
		static int sizeof_textCoordinates = sizeof(textCoordinates);
		static int sizeof_indices = sizeof(indices);

		static void load_basic_vertex_data() {}

		// apply specif transformations to the basic data
		static void load_specific_vertex_data(const glm::vec3& position, const glm::vec3& scale,
			const glm::vec3& rotationAxis, float rotationAngle)
		{
			// model matrix to be applied
			glm::mat4 modelTranslate = glm::translate(glm::mat4(1.0f), position);
			glm::mat4 modelRotate = glm::rotate(glm::mat4(1.0f), rotationAngle, rotationAxis);
			glm::mat4 modelScale = glm::scale(glm::mat4(1.0f), scale);
			glm::mat4 model = modelTranslate * modelRotate * modelScale;

			// y = model * x;
			glm::vec4 x, y;

			// first we build the vertices position
			for (unsigned int i = 0; i < N_VERTICES; i++)
			{
				x = { basic_vertices[3 * i + 0], basic_vertices[3 * i + 1], basic_vertices[3 * i + 2], 1 };
				y = model * x;
				vertices[3*i + 0] = y.x;
				vertices[3 * i + 1] = y.y;
				vertices[3 * i + 2] = y.z;
			}

			// then we build the normals
			//model = glm::transpose(glm::inverse(model));
			for (unsigned int i = 0; i < N_VERTICES; i++)
			{
				x = { basic_normals[3 * i + 0], basic_normals[3 * i + 1], basic_normals[3 * i + 2], 0 };
				y = model * x;
				normals[3 * i + 0] = y.x;
				normals[3 * i + 1] = y.y;
				normals[3 * i + 2] = y.z;
			}
		}

	}

}