#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>

class Screen
{
private:

	Screen();
	Screen(const Screen&);
	Screen& operator=(const Screen&);

private:

	SDL_Window* window;
	SDL_GLContext context;

public: 

	static Screen* Instance();

public:

	bool Initialize();
	void ClearScreen();
	void Render();
	void Shutdown();
};

#endif 