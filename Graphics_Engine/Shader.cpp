#include <iostream>
#include <fstream>

#include "Shader.h"

Shader* Shader::Instance()
{
	static Shader* shaderObject = new Shader();
	return shaderObject;
}

Shader::Shader()
{
	m_shaderProgramID = 0;
	m_vertexShaderID = 0;
	m_fragmentShaderID = 0;
}

GLuint Shader::GetShaderProgramID()
{
	return m_shaderProgramID;
}

bool Shader::CreateProgram()
{
	m_shaderProgramID = glCreateProgram();

	if (m_shaderProgramID == 0)
	{
		std::cout << "Unable to create ShaderProgram." << std::endl;
		return false;
	}

	return true;
}

bool Shader::CreateShaders()
{
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if (m_vertexShaderID == 0)
	{
		std::cout << "Unable to create Vertex Shader." << std::endl;
		return false;
	}

	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	
	if (m_fragmentShaderID == 0)
	{
		std::cout << "Unable to create Fragment Shader." << std::endl;
		return false;
	}

	return true;
}

bool Shader::CompileShaders(const std::string& filename, ShaderType shadertype)
{
	std::fstream file;
	std::string tempSourceCode;
	std::string text;
	GLuint shaderID;

	shaderID = (shadertype == ShaderType::VERTEX_SHADER) ? m_vertexShaderID : m_fragmentShaderID;

	file.open(filename);

	if (!file)
	{
		std::cout << "error reading file: " << filename << std::endl;
		return false;
	}

	while (!file.eof())
	{
		std::getline(file, text);
		tempSourceCode += text + "\n";
	}
	file.close();

	const GLchar* SourceCode = reinterpret_cast<const GLchar*>(tempSourceCode.c_str());

	glShaderSource(shaderID, 1, &SourceCode, nullptr);

	glCompileShader(shaderID);

	GLint errorCode;

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &errorCode);

	if (errorCode == GL_TRUE)
	{
		std::cout << "Shaders compiled successfully." << std::endl;
	}

	else
	{
		GLchar errorMessage[1000];
		GLsizei messageSize = 1000;

		glGetShaderInfoLog(shaderID, messageSize, &messageSize, errorMessage);

		std::cout << errorMessage << std::endl;
		return false;
	}

	return true;
}

bool Shader::AttachShaders()
{
	glAttachShader(m_shaderProgramID, m_vertexShaderID);
	glAttachShader(m_shaderProgramID, m_fragmentShaderID);

	return true;
}

bool Shader::LinkProgram()
{
	glLinkProgram(m_shaderProgramID);
	glUseProgram(m_shaderProgramID);

	GLint errorCode;

	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &errorCode);

	if (errorCode == GL_TRUE)
	{
		std::cout << "Linked program successfully." << std::endl;
	}

	else
	{
		GLchar errorMessage[1000];
		GLsizei messageSize = 1000;

		glGetProgramInfoLog(m_shaderProgramID, messageSize, &messageSize, errorMessage);

		std::cout << errorMessage << std::endl;
		return false;
	}

	return true;
}

void Shader::DetatchShaders()
{
	glDetachShader(m_shaderProgramID, m_vertexShaderID);
	glDetachShader(m_shaderProgramID, m_fragmentShaderID);
}

void Shader::DestroyShaders()
{
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}

void Shader::DestroyProgram()
{
	glDeleteProgram(m_shaderProgramID);
}

bool Shader::SendUniformData(const std::string& uniformName, GLint data)
{
	GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());

	if (ID == -1)
	{
		std::cout << "Shader variable " << uniformName << " not found or not used." << std::endl;
		return false;
	}

	glUniform1i(ID, data);
	return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLuint data)
{
	GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());

	if (ID == -1)
	{
		std::cout << "Shader variable " << uniformName << " not found or not used." << std::endl;
		return false;
	}

	glUniform1ui(ID, data);
	return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat data)
{
	GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());

	if (ID == -1)
	{
		std::cout << "Shader variable " << uniformName << " not found or not used." << std::endl;
		return false;
	}

	glUniform1f(ID, data);
	return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y)
{
	GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());

	if (ID == -1)
	{
		std::cout << "Shader variable " << uniformName << " not found or not used." << std::endl;
		return false;
	}

	glUniform2f(ID, x, y);
	return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z)
{
	GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());

	if (ID == -1)
	{
		std::cout << "Shader variable " << uniformName << " not found or not used." << std::endl;
		return false;
	}

	glUniform3f(ID, x, y, z);
	return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());

	if (ID == -1)
	{
		std::cout << "Shader variable " << uniformName << " not found or not used." << std::endl;
		return false;
	}

	glUniform4f(ID, x, y, z, w);
	return true;
}

bool Shader::SendUniformData(const std::string& uniformName, glm::mat4& data)
{
	GLuint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());

	if (ID == -1)
	{
		std::cout << "Shader variable " << uniformName << " not found or not in use." << std::endl;
		return false;
	}

	glUniformMatrix4fv(ID, 1, GL_FALSE, &data[0][0]);
	
	return true;
}
