#include <glad/glad.h>
#include <iostream>

#include "Screen.h"

#define WIDTH 1280
#define HEIGHT 720

Screen* Screen::Instance()
{
	static Screen* screen = new Screen;
	return screen;
}

Screen::Screen()
{
	window = nullptr;
	context = nullptr;
}

bool Screen::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "Unable to initilize SDL" << std::endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	window = SDL_CreateWindow("Graphics Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

	if (!window)
	{
		std::cout << "Error Creating Window" << std::endl;
		return false;
	}

	context = SDL_GL_CreateContext(window);

	if (!context)
	{
		std::cout << "Error Creating Context" << std::endl;
		return false;
	}

	if (!gladLoadGL())
	{
		std::cout << "Unable to load OpenGL Extensions! Quitting." << std::endl;
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void Screen::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::Render()
{
	SDL_GL_SwapWindow(window);
}

void Screen::Shutdown()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
