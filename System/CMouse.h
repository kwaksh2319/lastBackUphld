#pragma once

class CMouse
{
private:
	enum class Button { None, Down, Up, Press, DoubleClick };

	HWND handle;

	D3DXVECTOR2 position;

	short buttonStatus[8];
	short buttonPrevStatus[8];
	Button buttonMap[8];

	float wheelValue;
	float wheelPrevValue;
	float wheelMoveValue;

	DWORD doubleClickTime;
	DWORD startDoubleClickTime[8];
	int buttonCount[8];

public:
	CMouse(HWND handle);
	~CMouse();

	void WndProc(UINT iMessage, WPARAM wParam, LPARAM lParam);
	void Update();
	D3DXVECTOR2 Position() { return position; }

	bool Down(UINT button)
	{
		return buttonMap[button] == Button::Down;
	}

	bool Up(UINT button)
	{
		return buttonMap[button] == Button::Up;
	}

	bool Press(UINT button)
	{
		return buttonMap[button] == Button::Press;
	}

	bool DoubleClick(UINT button)
	{
		return buttonMap[button] == Button::DoubleClick;
	}

	float Wheel() { return wheelMoveValue; }
};
