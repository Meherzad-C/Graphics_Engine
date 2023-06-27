#include <gtc/matrix_transform.hpp>

#include "Light.h"
#include "Shader.h"
#include "Input.h"

Light::Light()
{
	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);
	m_position = glm::vec3(0.0f, 1.0f, 0.0f);

	m_model = glm::mat4(1.0f); 

	m_buffer.CreateBuffer(1);

	GLfloat vertices[] = { 0.0f, 0.0f, 0.0f };
	GLfloat colour[] = { 1.0f, 1.0f, 1.0f };

	m_buffer.FillVBO(Buffer::VBOType::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::FillType::SINGLE);
	m_buffer.FillVBO(Buffer::VBOType::COLOUR_BUFFER, colour, sizeof(colour), Buffer::FillType::SINGLE);

	m_buffer.LinkVBO("vertexIn", Buffer::VBOType::VERTEX_BUFFER, Buffer::ComponentType::XYZ, Buffer::DataType::FLOAT);
	m_buffer.LinkVBO("colourIn", Buffer::VBOType::COLOUR_BUFFER, Buffer::ComponentType::RGB, Buffer::DataType::FLOAT);
}

Light::~Light()
{
	m_buffer.DestroyBuffer();
}

void Light::Update()
{
	if (Input::Instance()->IsKeyPressed())

	{
		if (Input::Instance()->GetKeyDown() == 'i')
		{
			m_position.y += 0.001f;
		}

		else if (Input::Instance()->GetKeyDown() == 'k')
		{
			m_position.y -= 0.001f;
		}

		else if (Input::Instance()->GetKeyDown() == 'j')
		{
			m_position.x -= 0.001f;
		}

		else if (Input::Instance()->GetKeyDown() == 'l')
		{
			m_position.x += 0.001f;
		}

		/*else if (Input::Instance()->GetKeyDown() == 'u')
		{
			m_rotation.z -= 0.001f;
		}

		else if (Input::Instance()->GetKeyDown() == 'o')
		{
			m_rotation.z += 0.001f;
		}*/
	}

	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_position);
}

void Light::Render()
{
	Shader::Instance()->SendUniformData("model", m_model);
	Shader::Instance()->SendUniformData("isLit", false);
	Shader::Instance()->SendUniformData("isTextured", false);

	glPointSize(20.0f);
	m_buffer.Render(Buffer::DrawType::POINTS);
}

void Light::SendToShader()
{
	Shader::Instance()->SendUniformData("light.position", m_position.x, m_position.y, m_position.z);

	Shader::Instance()->SendUniformData("light.ambient", m_ambient.r, m_ambient.g, m_ambient.b);
	Shader::Instance()->SendUniformData("light.diffuse", m_diffuse.r, m_diffuse.g, m_diffuse.b);
	Shader::Instance()->SendUniformData("light.specular", m_specular.r, m_specular.g, m_specular.b);
}
