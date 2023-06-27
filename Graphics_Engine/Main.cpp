#include <glad/glad.h>
#include <iostream>
#include <SDL.h>

#include "Screen.h"
#include "Input.h"
#include "Shader.h"
#include "Quad.h"
#include "Cube.h"
#include "Camera.h"
#include "Light.h"


bool isAppRunning = true;



int main(int argc, char* argv[])
{
	Screen::Instance()->Initialize();

	Shader::Instance()->CreateProgram();
	Shader::Instance()->CreateShaders();

	Shader::Instance()->CompileShaders("../Shaders/shader.vert", Shader::ShaderType::VERTEX_SHADER);
	Shader::Instance()->CompileShaders("../Shaders/shader.frag", Shader::ShaderType::FRAGMENT_SHADER);

	Shader::Instance()->AttachShaders();
	Shader::Instance()->LinkProgram();

	float xPos = 0.0f;
	float yPos = 0.0f;


	//========================================================================================================================
	
	Quad quad;
	Cube cube;
	Camera camera;
	camera.Set3DView();
	Light light;

	//========================================================================================================================

	

	
	
	
	while (isAppRunning)
	{
		Screen::Instance()->ClearScreen();

		Input::Instance()->Update();

		char KeyPressed = Input::Instance()->GetKeyDown();

		isAppRunning = !Input::Instance()->IsXClicked();

		if (Input::Instance()->IsLeftButtonClicked())
		{
			std::cout << "Left mouse button pressed" << std::endl;
		}

		int mouseX = Input::Instance()->GetMousePositionX();
		int mouseY = Input::Instance()->GetMousePositionY();

		/*std::cout << "Mouse Positions- X: " << mouseX << "Y: " << mouseY << std::endl;*/

		camera.Update();

		light.Update();
		light.Render();
		light.SendToShader();

		/*quad.Update();
		quad.Render();*/

		cube.Update();
		cube.Render();

		Screen::Instance()->Render();
	}

	

	Shader::Instance()->DetatchShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();

	Screen::Instance()->Shutdown();

	system("pause");
	return 0;
}