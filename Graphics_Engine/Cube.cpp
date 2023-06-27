#include <gtc/matrix_transform.hpp>

#include "Cube.h"
#include "Shader.h"

Cube::Cube()
{
	GLfloat vertices[] = { -0.5f,  0.5f,  0.5f,
							0.5f,  0.5f,  0.5f,
							0.5f, -0.5f,  0.5f,
						   -0.5f, -0.5f,  0.5f,       //Front face

							0.5f,  0.5f, -0.5f,
						   -0.5f,  0.5f, -0.5f,
						   -0.5f, -0.5f, -0.5f,
							0.5f, -0.5f, -0.5f,       //Back face

						   -0.5f,  0.5f, -0.5f,
						   -0.5f,  0.5f,  0.5f,
						   -0.5f, -0.5f,  0.5f,
						   -0.5f, -0.5f, -0.5f,       //Left face

							0.5f,  0.5f,  0.5f,
							0.5f,  0.5f, -0.5f,
							0.5f, -0.5f, -0.5f,
							0.5f, -0.5f,  0.5f,       //Right face

						   -0.5f,  0.5f, -0.5f,
							0.5f,  0.5f, -0.5f,
							0.5f,  0.5f,  0.5f,
						   -0.5f,  0.5f,  0.5f,       //Top face

						   -0.5f, -0.5f,  0.5f,
							0.5f, -0.5f,  0.5f,
							0.5f, -0.5f, -0.5f,
						   -0.5f, -0.5f, -0.5f };    //Bottom face

	GLfloat colours[] = { 1.0f, 0.0f, 0.0f,	1.0f,
						 1.0f, 0.0f, 0.0f,	1.0f,
						 1.0f, 0.0f, 0.0f,	1.0f,
						 1.0f, 0.0f, 0.0f,	1.0f,    //Front face (red)
												 
						 0.0f, 1.0f, 0.0f,	1.0f,	 
						 0.0f, 1.0f, 0.0f,	1.0f,	 
						 0.0f, 1.0f, 0.0f,	1.0f,	 
						 0.0f, 1.0f, 0.0f,	1.0f,    //Back face (green)
												 
						 0.0f, 0.0f, 1.0f,	1.0f,	 
						 0.0f, 0.0f, 1.0f,	1.0f,	 
						 0.0f, 0.0f, 1.0f,	1.0f,	 
						 0.0f, 0.0f, 1.0f,	1.0f,    //Left face (blue)
												 
						 1.0f, 1.0f, 0.0f,	1.0f,	 
						 1.0f, 1.0f, 0.0f,	1.0f,	 
						 1.0f, 1.0f, 0.0f,	1.0f,	 
						 1.0f, 1.0f, 0.0f,	1.0f,    //Right face (yellow)
												 
						 1.0f, 0.0f, 1.0f,	1.0f,	 
						 1.0f, 0.0f, 1.0f,	1.0f,	 
						 1.0f, 0.0f, 1.0f,	1.0f,	 
						 1.0f, 0.0f, 1.0f,	1.0f,    //Top face (magenta)
												 
						 0.0f, 1.0f, 1.0f,	1.0f,
						 0.0f, 1.0f, 1.0f,	1.0f,
						 0.0f, 1.0f, 1.0f,	1.0f,
						 0.0f, 1.0f, 1.0f,	1.0f };    //Bottom face (cyan)

	GLfloat normals[] = {0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// Front face
						 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 
	
						 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,	// Back face
						 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
					
						 -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,	// Left face
						 -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 
	
						 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,	// Right Face
						 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 
	
						 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,	// Top Face
						 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
	
						 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,	// Bottom Face
						 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f };

	GLuint indices[] = { 0,  1,  3,  3,  1,  2,      //Front face
						 4,  5,  7,  7,  5,  6,      //Back face 
						 8,  9, 11, 11,  9, 10,      //Left face
						12, 13, 15, 15, 13, 14,      //Right face
						16, 17, 19, 19, 17, 18,      //Top face
						20, 21, 23, 23, 21, 22 };    //Bottom face

	m_buffer.CreateBuffer(36, true);

	m_buffer.FillEBO(indices, sizeof(indices), Buffer::FillType::SINGLE);

	m_buffer.FillVBO(Buffer::VBOType::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::FillType::SINGLE);
	m_buffer.FillVBO(Buffer::VBOType::COLOUR_BUFFER, colours, sizeof(colours), Buffer::FillType::SINGLE);
	m_buffer.FillVBO(Buffer::VBOType::NORMAL_BUFFER, normals, sizeof(normals), Buffer::FillType::SINGLE);

	m_buffer.LinkEBO();
	m_buffer.LinkVBO("vertexIn", Buffer::VBOType::VERTEX_BUFFER, Buffer::ComponentType::XYZ, Buffer::DataType::FLOAT);
	m_buffer.LinkVBO("colourIn", Buffer::VBOType::COLOUR_BUFFER, Buffer::ComponentType::RGBA, Buffer::DataType::FLOAT);
	m_buffer.LinkVBO("normalIn", Buffer::VBOType::NORMAL_BUFFER, Buffer::ComponentType::XYZ, Buffer::DataType::FLOAT);

	m_shininess = 50.f;
	m_position = glm::vec3(0.0f);
	m_ambient = glm::vec3(0.4f, 0.4f, 0.4f);
	m_diffuse = glm::vec3(0.1f, 0.7f, 0.2f);
	m_specular = glm::vec3(0.8f, 0.8f, 0.8f);
}

Cube::~Cube()
{
	m_buffer.DestroyBuffer();
}

void Cube::Update()
{
	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_position);
}

void Cube::Render()
{
	Shader::Instance()->SendUniformData("model", m_model);
	Shader::Instance()->SendUniformData("isLit", true);
	Shader::Instance()->SendUniformData("isTextured", false);

	Shader::Instance()->SendUniformData("material.shininess", m_shininess);

	Shader::Instance()->SendUniformData("material.ambient", m_ambient.r, m_ambient.g, m_ambient.b);
	Shader::Instance()->SendUniformData("material.diffuse", m_diffuse.r, m_diffuse.g, m_diffuse.b);
	Shader::Instance()->SendUniformData("material.specular", m_specular.r, m_specular.g, m_specular.b);

	m_buffer.Render(Buffer::DrawType::TRIANGLES);
}
