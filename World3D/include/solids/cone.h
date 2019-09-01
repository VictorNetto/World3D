#pragma once

#include <math.h>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace VertexData {

	namespace cone {

		static const float PI = atanf(1) * 4;

		static const int N_PHY = 36;
		static const float DELTA_PHY = 2 * PI / N_PHY;

		// 2 poles + N_PHY vertices
		static const int N_VERTICES = 2 + N_PHY;
		// 3 indices per triangle * number of triangles
		// number of triangles = 2 * N_PHY
		static const int N_INDICES = 6 * N_PHY;

		static float basic_vertices[3 * N_VERTICES];
		static float vertices[3 * N_VERTICES];
		static int indices[N_INDICES];

		static void supply_vertices()
		{
			// north pole
			basic_vertices[0] = 0.0f;  // x
			basic_vertices[1] = 0.0f;  // y
			basic_vertices[2] = 1.0f;  // z

			// south pole
			basic_vertices[3 * N_VERTICES - 3] = 0.0f;  // x
			basic_vertices[3 * N_VERTICES - 2] = 0.0f;  // y
			basic_vertices[3 * N_VERTICES - 1] = -1.0f;  // z

			// parallel
			for (int i = 0; i < N_PHY; i++)
			{
				int n = 3 + 3 * i;
				basic_vertices[n] = cosf(i * DELTA_PHY);      // x
				basic_vertices[n + 1] = sinf(i * DELTA_PHY);  // y
				basic_vertices[n + 2] = -1;                 // z
			}
		}

		static void supply_indices()
		{
			// poles
			for (int i = 0; i < N_PHY; i++)
			{
				// north
				// indices[0] to indices[3*N_PHY - 1]
				// vertices 0 (north pole) and [1, N_PHY] (first parallel)
				indices[3 * i] = 0;
				indices[3 * i + 1] = i + 1;
				indices[3 * i + 2] = i + 2;
				if (i == N_PHY - 1) indices[3 * i + 2] = 1;

				// south
				// indices[N_INDICES - 3*N_PHY] to indices[N_INDICES - 1]
				// vertices N_VERTICES - 1 (south pole) and [N_VERTICES - N_PHY - 1, N_VERTICES - 2]
				indices[N_INDICES - 1 - 3 * i] = N_VERTICES - 1;
				indices[N_INDICES - 1 - 3 * i - 1] = N_VERTICES - 1 - (i + 1);
				indices[N_INDICES - 1 - 3 * i - 2] = N_VERTICES - 1 - (i + 2);
				if (i == N_PHY - 1) indices[N_INDICES - 1 - 3 * i - 2] = N_VERTICES - 2;
			}
		}

		static int sizeof_vertices = sizeof(vertices);
		static int sizeof_indices = sizeof(indices);

		static void load_basic_vertex_data()
		{
			supply_vertices();
			supply_indices();
		}

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
				vertices[3 * i + 0] = y.x;
				vertices[3 * i + 1] = y.y;
				vertices[3 * i + 2] = y.z;
			}

			// then we build the normals
			//model = glm::transpose(glm::inverse(model));
			//for (unsigned int i = 0; i < N_VERTICES; i++)
			//{
			//	x = { basic_normals[3 * i + 0], basic_normals[3 * i + 1], basic_normals[3 * i + 2], 0 };
			//	y = model * x;
			//	normals[3 * i + 0] = y.x;
			//	normals[3 * i + 1] = y.y;
			//	normals[3 * i + 2] = y.z;
			//}
		}

	}

}