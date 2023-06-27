#ifndef QUAD_H
#define QUAD_H

#include <glad/glad.h>
#include <glm.hpp>

#include "Buffer.h"
#include "Texture.h"

class Quad
{
private:

	Buffer m_buffer;
	Texture m_texture;

	glm::mat4 m_model;
	glm::vec3 m_position;		// x,y position
	//glm::vec3 m_rotation;		// z rotation

	float m_shininess;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

public:

	Quad();
	~Quad();

	void Update();
	void Render();
};

#endif
