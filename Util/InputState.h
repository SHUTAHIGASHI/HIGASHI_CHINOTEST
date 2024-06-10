#pragma once

enum class InputType
{
	all,
	pause,	// 
	select,	// ���֍s���{�^��
	back,	// 
	right,	// �E
	left,	// ��
	up,		// ��
	down,	// ��
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

	// �}�E�X�J�[�\�����W�擾
	MousePos GetMousePos()const { return mousePos; }

private:
	// ���ꂼ��̓��͏��
	int mouseWheelState = 0;
	int lastPadState = 0;
	int padState = 0;
	int keyMouseState = 0;
	int lastKeyMouseState = 0;
	char keyState[256];
	char lastKeyState[256];
	// �}�E�X���W
	MousePos mousePos;
};