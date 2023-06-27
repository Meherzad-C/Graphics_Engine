#include <gtc/matrix_transform.hpp>
#include <iostream>

#include "Quad.h"
#include "Shader.h"
#include "Input.h"

Quad::Quad()
{
	// Data that represents verticies for a Quad

	GLfloat vertices[] = { -0.5f,	0.5f,	0.0f,
						   0.5f,	0.5f,	0.0f,
						   0.5f,   -0.5f,	0.0f,
						  -0.5f,   -0.5f,   0.0f };
													   
	GLfloat colours[] =  {	1.0f,	0.0f,	0.0f,	1.0f,
							0.0f,	0.0f,	1.0f,	1.0f,
							0.0f,	1.0f,	0.0f,	1.0f,
							0.0f,	1.0f,	1.0f,	1.0f };

	GLfloat normals[] = {	0.0f,	0.0f,	1.0f,
							0.0f,	0.0f,	1.0f, 
							0.0f,	0.0f,	1.0f,
							0.0f,	0.0f,	1.0f	};
													   
	GLfloat UVs[] =     {	0.0f,	1.0f,
							1.0f,	1.0f,
							1.0f,	0.0f,
							0.0f,	0.0f		};

	// Indices for the EBO Buffer
	GLuint indices[] = {	0,		1,		3,
							3,		1,		2	};

	m_buffer.CreateBuffer(6, true);

	m_buffer.FillEBO(indices, sizeof(indices), Buffer::FillType::SINGLE);

	m_buffer.FillVBO(Buffer::VBOType::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::FillType::SINGLE);
	m_buffer.FillVBO(Buffer::VBOType::COLOUR_BUFFER, colours, sizeof(colours), Buffer::FillType::SINGLE);
	m_buffer.FillVBO(Buffer::VBOType::NORMAL_BUFFER, normals, sizeof(normals), Buffer::FillType::SINGLE);
	m_buffer.FillVBO(Buffer::VBOType::TEXTURE_BUFFER, UVs, sizeof(UVs), Buffer::FillType::SINGLE);

	m_buffer.LinkEBO();
	m_buffer.LinkVBO("vertexIn", Buffer::VBOType::VERTEX_BUFFER, Buffer::ComponentType::XYZ, Buffer::DataType::FLOAT);
	m_buffer.LinkVBO("colourIn", Buffer::VBOType::COLOUR_BUFFER, Buffer::ComponentType::RGBA, Buffer::DataType::FLOAT);
	m_buffer.LinkVBO("normalIn", Buffer::VBOType::NORMAL_BUFFER, Buffer::ComponentType::XYZ, Buffer::DataType::FLOAT);
	m_buffer.LinkVBO("textureIn", Buffer::VBOType::TEXTURE_BUFFER, Buffer::ComponentType::UV, Buffer::DataType::FLOAT);

	m_texture.Load("../Assets/Textures/Crate_1.png");

	m_model = glm::mat4(1.0f);
	m_position = glm::vec3(0.0f);
	//m_rotation = glm::vec3(1.0f);

	m_shininess = 50.f;
	m_ambient = glm::vec3(0.4f, 0.4f, 0.4f);
	m_diffuse = glm::vec3(0.1f, 0.7f, 0.2f);
	m_specular = glm::vec3(0.8f, 0.8f, 0.8f);
}

Quad::~Quad()
{
	m_buffer.DestroyBuffer();
}

void Quad::Update()
{
	//if (Input::Instance()->IsKeyPressed())

	//{
	//	if (Input::Instance()->GetKeyDown() == 'i')
	//	{
	//		m_position.y += 0.001f;
	//	}

	//	else if (Input::Instance()->GetKeyDown() == 'k')
	//	{
	//		m_position.y -= 0.001f;
	//	}

	//	else if (Input::Instance()->GetKeyDown() == 'j')
	//	{
	//		m_position.x -= 0.001f;
	//	}

	//	else if (Input::Instance()->GetKeyDown() == 'l')
	//	{
	//		m_position.x += 0.001f;
	//	}

	//	/*else if (Input::Instance()->GetKeyDown() == 'u')
	//	{
	//		m_rotation.z -= 0.001f;
	//	}

	//	else if (Input::Instance()->GetKeyDown() == 'o')
	//	{
	//		m_rotation.z += 0.001f;
	//	}*/
	//}

	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_position);
	m_model = glm::rotate(m_model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	/*m_model = glm::scale(m_model, glm::vec3(0.5f, 0.5f, 1.0f));*/
}

void Quad::Render()
{
	Shader::Instance()->SendUniformData("model", m_model);
	Shader::Instance()->SendUniformData("isLit", false);
	Shader::Instance()->SendUniformData("isTextured", false);

	Shader::Instance()->SendUniformData("material.shininess", m_shininess);

	Shader::Instance()->SendUniformData("material.ambient", m_ambient.r, m_ambient.g, m_ambient.b);
	Shader::Instance()->SendUniformData("material.diffuse", m_diffuse.r, m_diffuse.g, m_diffuse.b);
	Shader::Instance()->SendUniformData("material.specular", m_specular.r, m_specular.g, m_specular.b);

	m_texture.Bind();
	m_buffer.Render(Buffer::DrawType::TRIANGLES);
	m_texture.Unbind();
}
