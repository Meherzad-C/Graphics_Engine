#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <glad/glad.h>

class Camera
{
protected:

	glm::mat4 m_view;
	glm::mat4 m_projection;

	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_up;

public:

	Camera();

	void Set3DView();
	void Update();
};

#endif
