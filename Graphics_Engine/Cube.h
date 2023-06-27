#ifndef CUBE_H
#define CUBE_H

#include <glm.hpp>
#include "Buffer.h"

class Cube
{
private:

	Buffer m_buffer;

	glm::mat4 m_model;
	glm::vec3 m_position;

	float m_shininess;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

public:

	Cube();
	~Cube();

	void Update();
	void Render();
};

#endif
