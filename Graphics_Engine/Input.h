#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

class Input
{
private:

	Input();
	Input(const Input&);
	Input& operator=(const Input&);

private:
	
	char m_keyUp;
	char m_keyDown;

	bool m_isXClicked;
	bool m_isKeyPressed;

	bool m_isRightButtonClicked;
	bool m_isLeftButtonClicked;
	bool m_isMiddleButtonClicked;

	int m_mouseMotionX;
	int m_mouseMotionY;

	int m_mousePositionX;
	int m_mousePositionY;

public:

	static Input* Instance();

public:

	bool IsXClicked();
	bool IsKeyPressed();

	char GetKeyUp();
	char GetKeyDown();

	bool IsRightButtonClicked();
	bool IsLeftButtonClicked();
	bool IsMiddletButtonClicked();

	int GetMouseMotionX();
	int GetMouseMotionY();

	int GetMousePositionX();
	int GetMousePositionY();

public:

	void Update();
};

#endif