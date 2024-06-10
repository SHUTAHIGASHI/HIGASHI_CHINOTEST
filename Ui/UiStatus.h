#pragma once
#include "Game.h"

class UiStatus
{
public:
	UiStatus();
	virtual ~UiStatus();

	void Init();
	void Draw();

	void DrawStatus();

	void UpdateUiData(int level, int point);
private:
	int SetDrawInfo(int i);
	std::string SetDrawText(int i);

private:
	// スコアボード画像
	int m_hScoreBoardImg;
	// 描画座標
	float m_posX;
	float m_posY;
	// 描画色
	int m_textColor;

private:
	// 現在のレベル
	int	m_boostLevelNum;
	// 現在のポイント
	int m_pointNum;
};

