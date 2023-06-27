#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "glad/glad.h"

class Texture
{
private:

	GLuint m_ID;

public:

	Texture();

	void Bind();
	bool Load(const std::string& filename);
	void Unload();
	void Unbind();
};

#endif 
