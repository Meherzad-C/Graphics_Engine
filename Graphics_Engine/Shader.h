#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm.hpp>

class Shader
{
private:

	Shader();
	Shader(const Shader&);
	Shader& operator=(const Shader&);

private:

	GLuint m_shaderProgramID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

public:

	static Shader* Instance();


public:

	enum class ShaderType { VERTEX_SHADER, FRAGMENT_SHADER };

public:

	GLuint GetShaderProgramID();

	bool CreateProgram();
	bool CreateShaders();

	bool CompileShaders(const std::string& filename, ShaderType shadertype);
	bool AttachShaders();
	bool LinkProgram();

	void DetatchShaders();
	void DestroyShaders();
	void DestroyProgram();

	bool SendUniformData(const std::string& uniformName, GLint data);
	bool SendUniformData(const std::string& uniformName, GLuint data);
	bool SendUniformData(const std::string& uniformName, GLfloat data);

	bool SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y);
	bool SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z);
	bool SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	bool SendUniformData(const std::string& uniformName, glm::mat4& data);
};

#endif
