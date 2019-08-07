#include "primitive.h"

static bool solidWasLoaded[NUM_SOLIDS];
static unsigned int _vaos[NUM_SOLIDS];
static unsigned int _nIndices[NUM_SOLIDS];

Shader Primitive::m_basicShader = Shader("./res/basicShader.vs", "./res/basicShader.fs");
Shader Primitive::m_lightingShader = Shader("./res/lightingShader.vs", "./res/lightingShader.fs");

extern const glm::vec3 LIGHT_COLOR = { 1, 1, 1 };
extern const glm::vec3 LIGHT_POSITION = { 0, 0, 0 };

static void init_solidWasLoaded_array()
{
	for (int i = 0; i < NUM_SOLIDS; i++)
	{
		solidWasLoaded[i] = false;
	}
}

static void load_cone()
{
	unsigned int cone_vbo, cone_vao, cone_ebo;
	cone::load();
	glGenVertexArrays(1, &cone_vao);
	glGenBuffers(1, &cone_vbo);
	glGenBuffers(1, &cone_ebo);
	_vaos[CONE] = cone_vao;
	_nIndices[CONE] = cone::N_INDICES;

	glBindVertexArray(cone_vao);

	glBindBuffer(GL_ARRAY_BUFFER, cone_vbo);
	glBufferData(GL_ARRAY_BUFFER, cone::sizeof_vertices, cone::vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cone_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cone::sizeof_indices, cone::indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

static void load_cube()
{
	unsigned int cube_vbo, cube_vao, cube_ebo;
	cube::load();
	glGenVertexArrays(1, &cube_vao);
	glGenBuffers(1, &cube_vbo);
	glGenBuffers(1, &cube_ebo);
	_vaos[CUBE] = cube_vao;
	_nIndices[CUBE] = cube::N_INDICES;

	glBindVertexArray(cube_vao);

	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
	glBufferData(GL_ARRAY_BUFFER, cube::sizeof_vertices, cube::vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube::sizeof_indices, cube::indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

static void load_cylinder()
{
	unsigned int cylinder_vbo, cylinder_vao, cylinder_ebo;
	cylinder::load();
	glGenVertexArrays(1, &cylinder_vao);
	glGenBuffers(1, &cylinder_vbo);
	glGenBuffers(1, &cylinder_ebo);
	_vaos[CYLINDER] = cylinder_vao;
	_nIndices[CYLINDER] = cylinder::N_INDICES;

	glBindVertexArray(cylinder_vao);

	glBindBuffer(GL_ARRAY_BUFFER, cylinder_vbo);
	glBufferData(GL_ARRAY_BUFFER, cylinder::sizeof_vertices, cylinder::vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylinder_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cylinder::sizeof_indices, cylinder::indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

static void load_sphere()
{
	unsigned int sphere_vbo, sphere_vao, sphere_ebo;
	sphere::load();
	glGenVertexArrays(1, &sphere_vao);
	glGenBuffers(1, &sphere_vbo);
	glGenBuffers(1, &sphere_ebo);
	_vaos[SPHERE] = sphere_vao;
	_nIndices[SPHERE] = sphere::N_INDICES;

	glBindVertexArray(sphere_vao);

	glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo);
	glBufferData(GL_ARRAY_BUFFER, sphere::sizeof_vertices, sphere::vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere::sizeof_indices, sphere::indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

static void load_cube_with_normals()
{
	unsigned int cube_with_normals_vbo[2], cube_with_normals_vao, cube_with_normals_ebo;
	cubeWithNormals::load();
	glGenVertexArrays(1, &cube_with_normals_vao);
	glGenBuffers(2, cube_with_normals_vbo);
	glGenBuffers(1, &cube_with_normals_ebo);
	_vaos[CUBE_WITH_NORMALS] = cube_with_normals_vao;
	_nIndices[CUBE_WITH_NORMALS] =  cubeWithNormals::N_INDICES;

	glBindVertexArray(cube_with_normals_vao);

	glBindBuffer(GL_ARRAY_BUFFER, cube_with_normals_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, cubeWithNormals::sizeof_vertices, cubeWithNormals::vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, cube_with_normals_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, cubeWithNormals::sizeof_normals, cubeWithNormals::normals, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_with_normals_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeWithNormals::sizeof_indices, cubeWithNormals::indices, GL_STATIC_DRAW);
}

static void load_sphere_with_normals()
{
	unsigned int sphere_with_normals_vbo[2], sphere_with_normals_vao, sphere_with_normals_ebo;
	sphereWithNormals::load();
	glGenVertexArrays(1, &sphere_with_normals_vao);
	glGenBuffers(2, sphere_with_normals_vbo);
	glGenBuffers(1, &sphere_with_normals_ebo);
	_vaos[SPHERE_WITH_NORMALS] = sphere_with_normals_vao;
	_nIndices[SPHERE_WITH_NORMALS] = sphereWithNormals::N_INDICES;

	glBindVertexArray(sphere_with_normals_vao);

	glBindBuffer(GL_ARRAY_BUFFER, sphere_with_normals_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sphereWithNormals::sizeof_vertices, sphereWithNormals::vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, sphere_with_normals_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sphereWithNormals::sizeof_normals, sphereWithNormals::normals, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_with_normals_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereWithNormals::sizeof_indices, sphereWithNormals::indices, GL_STATIC_DRAW);
}

static void load_solid(Solid solid, unsigned int* vao, unsigned int* nIndices, bool* m_withlighting)
{
	if (!solidWasLoaded[solid])
	{
		solidWasLoaded[solid] = true;
		switch (solid)
		{
		case CONE:
			load_cone();
			break;
		case CUBE:
			load_cube();
			break;
		case CYLINDER:
			load_cylinder();
			break;
		case SPHERE:
			load_sphere();
			break;
		case CUBE_WITH_NORMALS:
			load_cube_with_normals();
			break;
		case SPHERE_WITH_NORMALS:
			load_sphere_with_normals();
			break;
		default:
			break;
		}
	}

	if (solid == CONE || solid == CUBE || solid == CYLINDER || solid == SPHERE)
		*m_withlighting = false;
	else
		*m_withlighting = true;

	*vao = _vaos[solid];
	*nIndices = _nIndices[solid];
}

Primitive::Primitive()
	: x{ 0.0f }, y{ 0.0f }, z{ 0.0f },
	rotationState{ glm::mat4(1.0f) },
	scaleX{ 1.0f }, scaleY{ 1.0f }, scaleZ{ 1.0f }
{
}

Primitive::Primitive(float x, float y, float z, glm::mat4 rotationState,
	float scaleX, float scaleY, float scaleZ,
	Solid solid)
	: x{ x }, y{ y }, z{ z },
	rotationState{ rotationState },
	scaleX{ scaleX }, scaleY{ scaleY }, scaleZ{ scaleZ }
{
	load_solid(solid, &m_vao, &m_nIndices, &m_withlighting);
}

void Primitive::translate(float dx, float dy, float dz)
{
	x += dx;
	y += dy;
	z += dz;
}

void Primitive::rotate(float theta, float nx, float ny, float nz)
{
	float normalize_factor = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
	nx *= normalize_factor;
	ny *= normalize_factor;
	nz *= normalize_factor;

	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), theta, glm::vec3(nx, ny, nz));
	rotationState = rot * rotationState;
	glm::vec4 newPosition = rot * glm::vec4(x, y, z, 1.0f);
	x = newPosition.x;
	y = newPosition.y;
	z = newPosition.z;
}

void Primitive::draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos) const
{
	if (m_withlighting)
		draw_with_lighting(view, projection, viewPos);
	else
		draw_without_lighting(view, projection);
}

void Primitive::init()
{
	init_solidWasLoaded_array();

	m_basicShader.build();
	m_lightingShader.build();
}

void Primitive::draw_without_lighting(const glm::mat4& view, const glm::mat4& projection) const
{
	// set up the transformation
	glm::mat4 id4 = glm::mat4(1.0f);
	glm::mat4 model = glm::translate(id4, glm::vec3(x, y, z));
	model = model * rotationState * glm::scale(id4, glm::vec3(scaleX, scaleY, scaleZ));

	// use our basicShader and give it informations
	m_basicShader.use();
	m_basicShader.setMat4("model", model);
	m_basicShader.setMat4("view", view);
	m_basicShader.setMat4("projection", projection);
	m_basicShader.setVec3("objectColor", glm::vec3(color.red, color.green, color.blue));

	// finally draw the primitive
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_INT, 0);
}

void Primitive::draw_with_lighting(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos) const
{
	// set up the transformation
	glm::mat4 id4 = glm::mat4(1.0f);
	glm::mat4 model = glm::translate(id4, glm::vec3(x, y, z));
	model = model * rotationState * glm::scale(id4, glm::vec3(scaleX, scaleY, scaleZ));

	// use our lightingShader and give it informations
	m_lightingShader.use();
	m_lightingShader.setMat4("model", model);
	m_lightingShader.setMat4("view", view);
	m_lightingShader.setMat4("projection", projection);
	m_lightingShader.setVec3("objectColor", glm::vec3(color.red, color.green, color.blue));
	m_lightingShader.setVec3("lightColor", LIGHT_COLOR);
	m_lightingShader.setVec3("lightPos", LIGHT_POSITION);
	m_lightingShader.setVec3("viewPos", viewPos);
	// finally draw the primitive
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_INT, 0);
}