#pragma once

enum class InputType
{
	all,
	pause,	// 
	select,	// 次へ行くボタン
	back,	// 
	right,	// 右
	left,	// 左
	up,		// 上
	down,	// 下
	boost,
	space,
	end
};

struct MousePos
{
	int x = 0;
	int y = 0;
};

class InputState
{
public:
	bool IsTriggered(InputType type)const;
	bool IsPressed(InputType type)const;
	void Update();

	bool IsMouseWheel(bool isPlus)const;

	// マウスカーソル座標取得
	MousePos GetMousePos()const { return mousePos; }

private:
	// それぞれの入力状態
	int mouseWheelState = 0;
	int lastPadState = 0;
	int padState = 0;
	int keyMouseState = 0;
	int lastKeyMouseState = 0;
	char keyState[256];
	char lastKeyState[256];
	// マウス座標
	MousePos mousePos;
};