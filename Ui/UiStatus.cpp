#include "UiStatus.h"

namespace
{
	// スコアボード描画位置
	constexpr float kUIDrawSpaceX = 1615.0f;
	constexpr float kUIDrawSpaceY = 850.0f;
	// レベル表示の描画座標
	constexpr float kPosX = 1400.0f;
	constexpr float kPosY = kUIDrawSpaceY - 35.0f;
	constexpr float kPosSpace = 60.0f;

	// プレイヤー情報
	constexpr int kStatusNum = 2;

	// テキスト
	const char* const kTextBoost = "ブーストレベル : ";
	const char* const kTextPoint = "ポイント : ";
}

UiStatus::UiStatus() :
	m_hScoreBoardImg(-1),
	m_posX(0),
	m_posY(0),
	m_textColor(Game::kColorWhite),
	m_boostLevelNum(0),
	m_pointNum(0)
{
	m_hScoreBoardImg = LoadGraph("Data/ImageData/ScoreBoardImg.png");
	Init();
}

UiStatus::~UiStatus()
{
	DeleteGraph(m_hScoreBoardImg);
}

void UiStatus::Init()
{
	m_posX = kPosX;
	m_posY = kPosY;
}

void UiStatus::Draw()
{
	DrawRotaGraphF(kUIDrawSpaceX, kUIDrawSpaceY, 1, 0.0, m_hScoreBoardImg, true);

	DrawStatus();
}

void UiStatus::DrawStatus()
{
	std::string drawText;
	float drawX, drawY;
	int drawNum;

	for (int i = 0; i < kStatusNum; i++)
	{
		drawText = SetDrawText(i);
		drawNum = SetDrawInfo(i);
		drawX = m_posX, drawY = m_posY + (i * kPosSpace);

		DrawFormatStringF(drawX, drawY, m_textColor, "%s%d", drawText.c_str(), drawNum);
	}
}

void UiStatus::UpdateUiData(int level, int point)
{
	m_boostLevelNum = level;
	m_pointNum = point;
}

int UiStatus::SetDrawInfo(int i)
{
	if (i == 0)
	{
		return m_boostLevelNum;
	}
	else if (i == 1)
	{
		return m_pointNum;
	}

	return 0;
}

std::string UiStatus::SetDrawText(int i)
{
	if (i == 0)
	{
		return kTextBoost;
	}
	else if (i == 1)
	{
		return kTextPoint;
	}

	return "";
}
